Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;  

int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;
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
 

}
