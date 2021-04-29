#include <Zumo32U4.h>
#include <Servo.h>

//Replacing the lcd pins 0 and 1 for input and output of the sensor
int trigPin = 1;
int echoPin = 0;
long duration, cm , inches;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void ultraSonicSensor()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  cm = (duration/2) / 29.1;

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  //delay(50);
}


void loop() {
  ultraSonicSensor();
}
