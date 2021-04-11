
//Reading from the sensor using NewPing

#include <NewPing.h>

//Replacing the lcd pins 0 and 1 for the sensor
#define TRIGGER_PIN 1 
#define ECHO_PIN 0
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // initialize serial comm
  Serial.begin(9600);
}

void readUltraSonicSensor(){
  //read the sensors
  delay(50);
  int uS = sonar.ping();
  Serial.print(sonar.convert_cm(uS));
  Serial.println("cm");
  delay(50);
}

void loop() {
  readUltraSonicSensor();
}
