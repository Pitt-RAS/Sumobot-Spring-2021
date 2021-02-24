
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;

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

    //update LCD screen
    lcd.clear();  // clears screen
    lcd.gotoXY(0,0); // sets the position to x = 0, y = 0
    lcd.print("CL: " + countsLeft); //print the counts to the left
    lcd.gotoXY(7,0); // move the cursor to halfway down the line
    lcd.print("CR: " + countsRight); // print the count to the right
    lcd.gotoXY(0,1);
    lcd.print("MSL: " + motorSpeedLeft); //print the motor speed to the left
    lcd.gotoXY(7,1);
    lcd.print("MSR: " + motorSpeedRight); //print motor speed right
  }
}
