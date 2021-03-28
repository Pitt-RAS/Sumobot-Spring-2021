  
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
#include "detectedObject.h"
#include "TurnSensor.h"

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4LCD lcd;
Zumo32U4IMU imu;
 

// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;
unsigned long initialDelay = 1000;

//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

detectedObject origin; 

void setup() {
  buttonA.waitForButton(); 
  lcd.clear();
  turnSensorSetup(); 
  turnSensorReset(); 
  
  delay(initialDelay); 
  motors.setSpeeds(motorSpeedLeft, motorSpeedRight);
}

void loop() {    

    int16_t countsLeft = encoders.getCountsRight();
    int16_t countsRight = encoders.getCountsLeft();
    turnSensorUpdate(); 
    origin.updateDistance(countsLeft, getAngle()); 
    
    lcd.gotoXY(0,0); 
    lcd.print(origin.getBotAngle());     
    lcd.gotoXY(0,1); 
    lcd.print("theta");
     
    if( origin.getDistance() >= 20.0) {
      stopMotors(); 
    }
    
}

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }


/*function returns the turn angle read from the gyroscope in degrees*/
int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 
 }
