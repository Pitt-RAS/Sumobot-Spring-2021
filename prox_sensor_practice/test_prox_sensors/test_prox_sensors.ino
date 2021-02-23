/*
 * 
 * Author: Nathaniel Mallick
 * Date: 04/22/2021
 * 
 * This program test the 4 proximity sensors on the  ZUMO32U4
 * 
 * Each sensors value is displayed on the LCD 
 * 
 * If the sensor reads a value >= 5 (it reads a max value of 5) then the buzzer goes off
 * 
*/ 

#include <Wire.h> 
#include <Zumo32U4.h> 

Zumo32U4Buzzer buzzer;
Zumo32U4LCD lcd; 
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA; 

  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 8; // On scale of 0-15

void setup() {
  
  proxSensors.initThreeSensors(); 
  buttonA.waitForButton(); // Wait for button A to be pressed to start 
}


void loop() {
  /*Read Sensors*/
  proxSensors.read(); 
  int sensors[4];
  sensors[0] = proxSensors.countsLeftWithLeftLeds();
  sensors[1] = proxSensors.countsFrontWithLeftLeds();
  sensors[2] = proxSensors.countsFrontWithRightLeds();
  sensors[3] = proxSensors.countsRightWithRightLeds();

  /*LCD Display, to values of each sensor*/
  lcd.gotoXY(0, 1);
  lcd.print(sensors[0]);
  lcd.print(" "); 
  lcd.print(sensors[1]);
  lcd.print(" "); 
  lcd.print(sensors[2]);
  lcd.print(" "); 
  lcd.print(sensors[3]);
  lcd.print(" "); 

  /*Check each sensor and buzz if it reads a value of 5 or greater*/
  for(int i = 0; i < 4; i++) {
    if(sensors[i] >= 5) {
        buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer
      }
    }
  
}
