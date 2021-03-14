 /*
 *ZUMO PROJECT 1
 *AUTHORS: Justin Cacal and Nate Mallick
 *
 *Updated: February 28, 2021
 *
 *Separates the start zumo bot and gyroscope calibration to their own buttons (A/B)
 *Tunes the gyroscope
 *Implement side sensors to deal with wall detection
 *
*/

#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include <PID.h>


Zumo32U4IMU imu;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;


// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;

unsigned long initialDelay = 1000;


//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

void setup() {
  /*Set PID*/
  setPID(0,0,0);
  
  /*Set up gyroscope*/
  turnSensorSetup(); //Wait for button B to calibrate turn sensor 
  buttonA.waitForButton(); // Wait for button A to be pressed to start
  
  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 10; // On scale of 0-15
  
  
  buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer
  delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A
  lastEncoderTime = millis(); //sets initial value
  proxSensors.initThreeSensors(); // configures proxSensors to use all three sensors
  
}

void loop() {    
  /*conditional statement 
   *if we detect object we stop and turn else the bot moves forward*/
      if(isObject()) {
          turn(); 
        } else {
          motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Run motors at specified speeds
          readMotorValues();//read encoder data to correct trajectory
          }
}

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }

/*Function to determine if obstacle is in front of bot*/
bool isObject() {

    /*Removed side proxSensors to just deal with front sensors (for now)*/

    /*Reads the value from the front two sensors and returns true or false
     *true : if front sensors read 6 or greater
    */
    proxSensors.read();
    if (proxSensors.countsFrontWithLeftLeds() >= 6 || proxSensors.countsFrontWithRightLeds() >= 6){
      return true; 
    } else {
      return false;
    }
}


void turn(){
  
    //turnSensorUpdate();
    
    while(1){
      turnSensorUpdate();
      /*turns the bot until the gyroscope reads an angle of 35 degrees*/

     
      //Turn V1
      /*
      if(getAngle()<35 && getAngle()>0 ) {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
        } else if(getAngle()>-35 && getAngle()< 0 ) {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
        } else {
          motors.setSpeeds(0,0); 
          break;
          }
       */

       //Turn V2
       /*
       if(proxSensors.countsLeftWithLeftLeds() >=6) {
        turnSensorReset();
        do {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight);
          turnSensorUpdate(); 
        } while(getAngle()>-35 && getAngle()<0);
        break;
  
       } else if(proxSensors.countsRightWithRightLeds() >=6) {
        turnSensorReset();
        do {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight);
          turnSensorUpdate(); 
        } while(getAngle()<35 && getAngle()>0);
        break;
       }
       else {
        if(getAngle()<35 && getAngle()>0) {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
        } else if(getAngle()>-35 && getAngle()<0) {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
        } else {
          motors.setSpeeds(0,0); 
          break;
          }
       }
       */

       if(proxSensors.countsLeftWithLeftLeds() > proxSensors.countsRightWithRightLeds()) {
        turnSensorUpdate();
        do {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight);
          turnSensorUpdate(); 
        } while(getAngle()>-35 && getAngle()<0);
        break;
  
       } else if(proxSensors.countsRightWithRightLeds() > proxSensors.countsLeftWithLeftLeds()) {
        turnSensorUpdate();
        do {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight);
          turnSensorUpdate(); 
        } while(getAngle()<35 && getAngle()>0);
        break;
       }
       else {
        
        
        if(getAngle()<35 && getAngle()>0) {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
        } else if(getAngle()>-35 && getAngle()<0) {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
        } else {
          motors.setSpeeds(0,0); 
          break;
          }
          
/*
          if(proxSensors.countsFrontWithRightLeds() > proxSensors.countsFrontWithLeftLeds()) {
            turnSensorUpdate();
            do {
              motors.setSpeeds(-motorSpeedLeft, motorSpeedRight);
            } while(getAngle()<35 && getAngle()>0);
            break;
          } else if(proxSensors.countsFrontWithLeftLeds() > proxSensors.countsFrontWithRightLeds()) {
            turnSensorUpdate();
            do {
              motors.setSpeeds(motorSpeedLeft, -motorSpeedRight);
            } while(getAngle()>-35 && getAngle()<0);
            break;
          } else {
            turnSensorUpdate();
            if(getAngle()<35 && getAngle()>0) {
              motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
            } else if(getAngle()>-35 && getAngle()<0) {
              motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
            } else {
              motors.setSpeeds(0,0); 
              break;
              }
          }
        }
        */
       }
      }
       turnSensorReset(); //Reset gyroscope 
}


/*Displays motors onto LCD*/
void readMotorValues(){
    //reads encoders and adjusts speeds every 100 ms
  if ((millis() - lastEncoderTime) >= 100)
  {
    lastEncoderTime = millis();
    int16_t countsLeft = encoders.getCountsAndResetLeft();
    int16_t countsRight = encoders.getCountsAndResetRight();

    /*adjusts speed based on encoder data*/
    if(countsLeft < countsRight){
      motorSpeedLeft += 1;
      motorSpeedRight -= 1;
    } else if (countsLeft > countsRight){
      motorSpeedLeft -= 1;
      motorSpeedRight += 1;
    }

    Serial.print(countsLeft);
    Serial.print("\t");
    Serial.print(countsRight);
    Serial.print("\t");
    Serial.print(motorSpeedLeft);
    Serial.print("\t");
    Serial.print(motorSpeedRight);
    Serial.print("\n"); 

    /*Removed CR and CL since string length is interfering with LCD display capacity*/
    /* update LCD screen*/
    lcd.clear();  // clears screen
    lcd.gotoXY(0,0); // sets position to line 
    lcd.print(countsLeft); // displays the countsLeft encoder
    lcd.gotoXY(0,1);
    lcd.print(countsRight);// displays the countsRight encoder
  }
}


/*function returns the turn angle read from the gyroscope in degrees*/
int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

 }
