/*
*PREPARING SENSORS FOR READING AND MERGING SOME BLOCKS OF THE CODE INTO FUNCTIONS
*/
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;

// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;

//Initialize LCD screen -- create LCD object
Zumo32U4LCD lcd;

//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

void setup() {
  buttonA.waitForButton(); // Wait for button A to be pressed to start

  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 10; // On scale of 0-15

  buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer

  unsigned long initialDelay = 1000;
  delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A

  lastEncoderTime = millis(); //sets initial value

  // For this configuration to work, jumpers on the front sensor array must
  // be installed in order to connect pin 20 to LFT and connect pin 4 to RGT.
  proxSensors.initThreeSensors(); // configures proxSensors to use all three sensors
}

void loop() {
  motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Run motors at specified speeds

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

  // reads the proximity sensors
  proxSensors.read();

  /*Removed side proxSensors to just deal with front sensors (for now)*/
  // stop both motors if an object is detected close to the front of the vehicle
  if (proxSensors.countsFrontWithLeftLeds() == 6 || proxSensors.countsFrontWithRightLeds() == 6){
    motorSpeedLeft = 0;
    motorSpeedRight = 0;
  }
}
