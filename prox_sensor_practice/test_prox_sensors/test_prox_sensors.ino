/*
 * 
 * Author: Nathaniel Mallick, Justin Cacal 
 * Date: 04/22/2021
 * 
 * This program test the 4 proximity sensors on the  ZUMO32U4
 * Each sensors value is displayed on the LCD 
 * If the sensor reads a value >= 5 (it reads a max value of 5) then the buzzer goes off
 * 
 * Update (A): 04/23/2021
 * 
 * Left and right sensors read in values and adjust the bot away from detected object
 * 
 * i.e left sensor (sensors[0]) reads a five - bot rotates clockwise
 *     right sensor(sensors[3]) reads a five - bot rotates counterclockwise
 * 
 * 
 * Update (B): 04/23/2021
 * 
 * Bot will turn ~180 degrees if it detects an object directly in front of it
 * (IT LOOPS SO HAVE A CLEAR SURROUNDING)
*/ 

#include <Wire.h> 
#include <Zumo32U4.h> 
#include "TurnSensor.h"

Zumo32U4Buzzer buzzer;
Zumo32U4LCD lcd; 
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors; 
Zumo32U4ButtonA buttonA; 
Zumo32U4IMU imu;

  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 8; // On scale of 0-15

  //Motor speeds
  int16_t left = 100;
  int16_t right = 100; 
  
void setup() {
  buttonA.waitForButton(); // Wait for button A to be pressed to start 
  turnSensorSetup(); 
  delay(500); 
  turnSensorReset(); 
  proxSensors.initThreeSensors(); 
  
}


void loop() {
  
  
  /*Read Sensors*/
  int32_t angle = getAngle(); 
  int sensors[4];
  readSensors(sensors); 
  turnSensorUpdate(); 
  
  /*LCD Display, to values of each sensor*/
  printToLcd(sensors);

//UN-NOTE ME FOR PART A
  /******************************************************************************************/
             
//  Check each sensor and buzz if it reads a value of 5 or greater*/
//    /*Second param changes the distance of detection 0 - 5*/
//    //alert(sensors, 5); 
//
//  /*if sensors[0] or sensors[3] detects something on the left or right side(respectively) 
//  **the bot, we rotate clockwise/counterclockwise*/
//  if(sensors[0]>=5) {
//    motors.setSpeeds(left, -right);
//  } else if(sensors[3]>=5) {
//    motors.setSpeeds(-left, right);
//  } else {
//    motors.setSpeeds(0,0);  
//      }

/*****************************************************************************************/


//PART B 
/*****************************************************************************************/
 
  /*If something is in front of the bot, it will turn ~180 degrees*/
  /*NOTE: this loops so if the bot is surround by objects it will keep spinning*/
  
  if(sensors[1]>=5 && sensors[2]>=5) {
    turnSensorUpdate();
    while(1){
    printToLcd(sensors);
    turnSensorUpdate();
    
    /*STOPS BETWEEN 170 ~ 180 AND -170 ~ -180*/
    if(getAngle()<170 && getAngle()>0 ) {
        motors.setSpeeds(-left, right); 
      } else if(getAngle()>-170 && getAngle()< 0 ) {
        motors.setSpeeds(left, -right); 
      } else {
        motors.setSpeeds(0,0); 
        break;
        }
    }
    readSensors(sensors);  
    turnSensorReset(); //Reset gyroscope 
  }

/*****************************************************************************************/


  

}


/*Created Functions*/
/******************************************************************************************/
void alert(int sensors[4], int n) {
    for(int i = 0; i < 4; i++) {
    if(sensors[i] >= n) {
        buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer
      }
    }
  }

void readSensors(int sensors[4]) {

    proxSensors.read(); 
    sensors[0] = proxSensors.countsLeftWithLeftLeds();
    sensors[1] = proxSensors.countsFrontWithLeftLeds();
    sensors[2] = proxSensors.countsFrontWithRightLeds();
    sensors[3] = proxSensors.countsRightWithRightLeds();  
  
  }
void printToLcd(int sensors[4]){
    lcd.gotoXY(0, 0); 
    lcd.print(getAngle()); 
    lcd.print(" "); 
    lcd.gotoXY(0, 1);
    lcd.print(sensors[0]);
    lcd.print(" "); 
    lcd.print(sensors[1]);
    lcd.print(" "); 
    lcd.print(sensors[2]);
    lcd.print(" "); 
    lcd.print(sensors[3]);
    lcd.print(" "); 
  
  }

  int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

    }

void turnAround(){
    if(sensors[1]>=5 && sensors[2]>=5) {
    turnSensorUpdate();
    while(1){
    printToLcd(sensors);
    turnSensorUpdate();
    
    /*STOPS BETWEEN 170 ~ 180 AND -170 ~ -180*/
    if(getAngle()<170 && getAngle()>0 ) {
        motors.setSpeeds(-left, right); 
      } else if(getAngle()>-170 && getAngle()< 0 ) {
        motors.setSpeeds(left, -right); 
      } else {
        motors.setSpeeds(0,0); 
        break;
        }
    }
    readSensors(sensors);  
    turnSensorReset(); //Reset gyroscope 
  }
}