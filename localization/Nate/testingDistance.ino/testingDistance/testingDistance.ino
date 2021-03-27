
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


Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4LCD lcd;

 

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
  
  delay(initialDelay); 
  motors.setSpeeds(motorSpeedLeft, motorSpeedRight);
}

void loop() {    

    int16_t countsLeft = encoders.getCountsRight();
    int16_t countsRight = encoders.getCountsLeft();
   
    
    lcd.print(countsLeft);     
    if( origin.convert(countsLeft) >= 20.0) {
      stopMotors(); 
    }
    
}

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }


/*Displays motors onto LCD*/
//void displayMotorValues(int16_t encoder){
//    lcd.clear(); 
//    lcd.print(encoder); // displays the countsLeft encoder 
//}
