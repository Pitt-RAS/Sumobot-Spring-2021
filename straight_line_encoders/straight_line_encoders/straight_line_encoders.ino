
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;

// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 150;
int16_t motorSpeedRight = 150;

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
    Serial.print(countsLeft);
    Serial.print("\t");
    Serial.print(countsRight);
    Serial.print("\t");
    Serial.print(motorSpeedLeft);
    Serial.print("\t");
    Serial.print(motorSpeedRight);
    Serial.print("\n");

    // temporarily hijacking the lcd to test the proximity sensors
    //update LCD screen
    //lcd.clear();  // clears screen
    //lcd.gotoXY(0,0); // sets position to line 1
    //lcd.print( "CL: " + countsLeft); // displays the countsLeft
    //lcd.gotoXY(0,1);
    //lcd.print( "CR: " + countsRight);
  }

  // reads the proximity sensors
  proxSensors.read();

  // displaying proximity sensor output to lcd to test sensitivity
  lcd.gotoXY(0,0);
  lcd.print("FL: ");
  lcd.print(proxSensors.countsFrontWithLeftLeds());
  lcd.gotoXY(0,1);
  lcd.print("FR: ");
  lcd.print(proxSensors.countsFrontWithRightLeds());
  lcd.gotoXY(7,0);
  lcd.print(proxSensors.countsLeftWithLeftLeds());
  lcd.gotoXY(7,1);
  lcd.print(proxSensors.countsRightWithRightLeds());

  // stop both motors if an object is detected close to the front of the vehicle
  if (proxSensors.countsFrontWithLeftLeds() == 6 || proxSensors.countsFrontWithRightLeds() == 6 ||
      proxSensors.countsLeftWithLeftLeds() == 6 || proxSensors.countsRightWithRightLeds() == 6)
  {
    motorSpeedLeft = 0;
    motorSpeedRight = 0;
  }
}
