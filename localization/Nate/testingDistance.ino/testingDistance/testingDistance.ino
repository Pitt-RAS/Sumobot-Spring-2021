
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




Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4LCD lcd;


// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 200;
int16_t motorSpeedRight = 25;

unsigned long initialDelay = 1000;


//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

void setup() {
  
  
  
  buttonA.waitForButton(); // Wait for button A to be pressed to start  
  
  delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A
  //lastEncoderTime = millis(); //sets initial value
  motors.setSpeeds(motorSpeedLeft, motorSpeedRight);
  
}

void loop() {    
    //lastEncoderTime = millis();
    int16_t countsLeft = encoders.getCountsRight();
    int16_t countsRight = encoders.getCountsLeft();
    displayMotorValues(countsLeft, countsRight); 
//    if(countsLeft >= 909.7) {
//      stopMotors(); 
//    }
    
}

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }


/*Displays motors onto LCD*/
void displayMotorValues(int16_t countsLeft,int16_t countsRight){
    //reads encoders and adjusts speeds every 100 ms
  

    /*adjusts speed based on encoder data*/
//    if(countsLeft < countsRight){
//      motorSpeedLeft += 1;
//      motorSpeedRight -= 1;
//    } else if (countsLeft > countsRight){
//      motorSpeedLeft -= 1;
//      motorSpeedRight += 1;
//    }

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
