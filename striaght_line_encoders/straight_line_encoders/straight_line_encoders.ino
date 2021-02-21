
#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;

// Initial speeds for left and right motors (0-400)
int16_t initialMotorSpeedLeft  = 150;
int16_t initialMotorSpeedRight = 150;

void setup() { 
  buttonA.waitForButton(); // Wait for button A to be pressed to start

  // Buzzer variables in case they need to be changed
  unsigned int buzzerFrequency = 261; // Middle C
  unsigned int buzzerDuration =  50; // In milliseconds
  unsigned char buzzerVolume = 10; // On scale of 0-15
  
  buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer

  unsigned long initialDelay = 1000;
  delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A

  
}

void loop() {
  motors.setSpeeds(initialMotorSpeedLeft, initialMotorSpeedRight); // Run motors at specified speeds

}
