/*
*PREPARING SENSORS FOR READING AND MERGING SOME BLOCKS OF THE CODE INTO FUNCTIONS
*/
#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

Zumo32U4IMU imu;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;

//Prototype functions
void readMotorValues();

// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;

unsigned long initialDelay = 1000;


//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

void setup() {
  
  turnSensorSetup();
  
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
  // reads the proximity sensors
      
      if(isObject()) {
        stopMotors();
 //         motors.setSpeeds(-motorSpeedLeft,-motorSpeedRight);

          
//          int16_t countsLeft = encoders.getCountsAndResetLeft();
//          int16_t countsRight = encoders.getCountsAndResetRight();
//      
//          //adjusts speed based on encoder data
//          if(countsLeft < countsRight){
//            motorSpeedLeft += 1;
//            motorSpeedRight -= 1;
//          } else if (countsLeft > countsRight){
//            motorSpeedLeft -= 1;
//            motorSpeedRight += 1;
//          }
        
          
        /**********************************/
        turn(); 
        } else {
          motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Run motors at specified speeds
          readMotorValues();        
          }

   
  
}


void stopMotors() {
  motors.setSpeeds(0, 0);
  }

  
bool isObject() {

    /*Removed side proxSensors to just deal with front sensors (for now)*/
  // stop both motors if an object is detected close to the front of the vehicle
    proxSensors.read();
  if (proxSensors.countsFrontWithLeftLeds() >= 5 || proxSensors.countsFrontWithRightLeds() >= 5){
    return true; 
  } else {return false;}
  
  }

void turn(){
    turnSensorUpdate();
    
    
    while(1){
      turnSensorUpdate();
      
      /*STOPS BETWEEN 170 ~ 180 AND -170 ~ -180*/
      if(getAngle()<35 && getAngle()>0 ) {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
        } else if(getAngle()>-35 && getAngle()< 0 ) {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
        } else {
          motors.setSpeeds(0,0); 
          break;
          }
      }  
      turnSensorReset(); //Reset gyroscope 
  
}


//Displays motors onto LCD
void readMotorValues(){
    //reads encoders and adjusts speeds every 100 ms
  if ((millis() - lastEncoderTime) >= 100)
  {
    lastEncoderTime = millis();
    int16_t countsLeft = encoders.getCountsAndResetLeft();
    int16_t countsRight = encoders.getCountsAndResetRight();

    //adjusts speed based on encoder data
    if(countsLeft < countsRight){
      motorSpeedLeft += 1;
      motorSpeedRight -= 1;
    } else if (countsLeft > countsRight){
      motorSpeedLeft -= 1;
      motorSpeedRight += 1;
    }

          /*Might delete if not necessary*/
//    Serial.print(countsLeft);
//    Serial.print("\t");
//    Serial.print(countsRight);
//    Serial.print("\t");
//    Serial.print(motorSpeedLeft);
//    Serial.print("\t");
//    Serial.print(motorSpeedRight);
//    Serial.print("\n"); 

    // update LCD screen
    lcd.clear();  // clears screen

    /*Removed CR and CL since string length is interfering with LCD display capacity*/
    lcd.gotoXY(0,0); // sets position to line 
    lcd.print(countsLeft); // displays the countsLeft encoder
    lcd.gotoXY(0,1);
    lcd.print(countsRight);// displays the countsRight encoder
  }
}

int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

 }
