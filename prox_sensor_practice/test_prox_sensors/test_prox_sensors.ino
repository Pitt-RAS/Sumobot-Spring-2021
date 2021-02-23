/*
 * 
 * Author: Nathaniel Mallick
 * Date: 04/22/2021
 * 
 * This program test the 4 proximity sensors on the  ZUMO32U4
 * Each sensors value is displayed on the LCD 
 * If the sensor reads a value >= 5 (it reads a max value of 5) then the buzzer goes off
 * 
 * Updated: 04/23/2021
 * 
 * Left and right sensors read in values and adjust the bot away from detected object
 * 
 * i.e left sensor (sensors[0]) reads a five - bot rotates clockwise
 *     right sensor(sensors[3]) reads a five - bot rotates counterclockwise
 * 
*/ 

#include <Wire.h> 
#include <Zumo32U4.h> 

Zumo32U4Buzzer buzzer;
Zumo32U4LCD lcd; 
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors; 
Zumo32U4ButtonA buttonA; 

  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 8; // On scale of 0-15

  //Motor speeds
  int16_t left = 100;
  int16_t right = 100; 
  
void setup() {
  
  proxSensors.initThreeSensors(); 
  buttonA.waitForButton(); // Wait for button A to be pressed to start 
}


void loop() {
  /*Read Sensors*/
  int sensors[4];
  readSensors(sensors); 

  /*LCD Display, to values of each sensor*/
  printToLcd(sensors); 
  

  /*Check each sensor and buzz if it reads a value of 5 or greater*/
  /*Second param changes the distance*/
  //alert(sensors, 5);

  /*if sensors[0] or sensors[3] detects something on the left or right side(respectively) 
  **the bot, we rotate clockwise/counterclockwise*/
  if(sensors[0]>=5) {
    motors.setSpeeds(left, -right);
  } else if(sensors[3]>=5) {
    motors.setSpeeds(-left, right);
  } else {
    motors.setSpeeds(0,0);  
      }
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
