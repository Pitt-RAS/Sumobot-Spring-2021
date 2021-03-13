/*
 *ZUMO PROJECT 1
 *AUTHORS: 2021 Sumo Bot Team
 *
 *Updated: February 28, 2021
 *
 *Demonstration of wall detection using front proximity sensors, 
 *corrections using encoder data, utilizing gyroscope for fixed rotation
 *
*/

#include <Wire.h>
#include <Zumo32U4.h>
#include <math.h>
#include "TurnSensor.h"
#include "src/PID/PID.h"


Zumo32U4IMU imu;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;
PID motorController;


// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;

unsigned long initialDelay = 1000;


void setup() {
  
  /*Set up gyroscope*/
  turnSensorSetup(); 
  buttonA.waitForButton(); // Wait for button A to be pressed to start
  
  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 10; // On scale of 0-15
  
  
  buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer
  delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A
  proxSensors.initThreeSensors(); // configures proxSensors to use all three sensors
  motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Start motors
  straightLineReset(); // Setup motorController PID object
}

void loop() {    
  
  /*conditional statement 
   *if we detect object we stop and turn else the bot moves forward*/
      if(isObject()) {
          turn();
          straightLineReset(); // This is needed following the use of the turn function only if motorController is not used by the turn function
      }
      else
      {
          straightLine();
      }    
}

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }


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

// This function resets the motorController PID object
void straightLineReset()
{
    /* Sets motorController's kp, ki, and kd values and resets the PID object's timer and integral error values
    This is needed whenever resuming use of motorController following an idle period to avoid storing arbitrarily large amounts of integral error on resume*/
    motorController.setPID(1.0, 1.0, 1.0);
}

void straightLine(){

    // Read encoder values
    int16_t countsLeft = encoders.getCountsAndResetLeft();
    int16_t countsRight = encoders.getCountsAndResetRight();

    /* Pass the desired setPoint: (0.0) and feedback state: (countsLeft - countsRight) into motorController's PID.error_correction method
    Use the returned value to adjust the left and right motor speed settings */
    int16_t adjustment = (int) round(motorController.error_correction(0.0, countsLeft - countsRight));
    motorSpeedLeft += adjustment;
    motorSpeedRight -= adjustment;

    // Print encoder and motor values to Serial monitor
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


/*function returns the turn angle read from the gyroscope in degrees*/
int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

 }
