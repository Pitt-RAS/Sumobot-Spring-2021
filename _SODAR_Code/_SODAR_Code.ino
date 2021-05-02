/*  ORGANIZATION: Pitt-RAS
 *  AUTHORS:      Sumobot Spring 2021 Team
 *  DATE:         5/1/2021
 *  DESCRIPTION:
 *    PID-Controlled Straight Line Driving with object avoidance using Infred sensors.
 *    Ultrsonic sensor finds the direction of the furthest path and orients the bot to drive in said direction. 
 */

#include <Wire.h>
#include <Servo.h>  //Arduino Servo Library 
#include <Zumo32U4.h>  //Zumobot Library 
#include "Turnsensor.h" //Turnsensor library for turning measurement 

const uint16_t maxSpeed = 400;  //max speed of sumo

//Instantiation of all Zumo classes + External Arduino Servo class
Servo servo;
Zumo32U4IMU imu;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonC buttonC;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LineSensors lineSensors;

//PID Variables
float Kp = 0.4; // Proportional Term
float Kd = 9; // Derivative Term
float Ki = 0; // Integral Term

double previousTime = 0;
double totalError = 0; // Accumulated Error
double lastError = 0; // Error from last sensor reading.
double derivError; // Derivative of error taken over the last time step

//straightState/turnState
int16_t motorSpeedLeft  = 300;// Initial speeds for left and right motors (0-400)
int16_t motorSpeedRight = 300;
unsigned long int lastEncoderTime; //declare for use in encoder adjustment

//Replacing the lcd pins 0 and 1 for input and output of the sensor
int trigPin = 1;
int echoPin = 0;

//Buzzer Melody Variables
unsigned int buzzerFrequency = 261; // Middle C
unsigned int buzzerDuration =  400; // In milliseconds
unsigned char buzzerVolume = 10; // On scale of 0-15
unsigned int initialDelay = 1000; //1 second

//Variables for reading Ultrasonic sensor 
long duration, cm , inches;

//Variables for finding the longest Distance
int pathCorrect; 
int currentDist, longestDist, longestDirection;

//state enum declaration
enum States { Idle, CalibrateStraight, Straight, Turn, findPath };
States state = Idle;


void setup()
{
  //motors.flipLeftMotor(true);   //Needed if motor polarity is reversed  
  //motors.flipRightMotor(true);

  pinMode(trigPin, OUTPUT);       //Initialize US triggering + echo pins to Zumo LCD pins
  pinMode(echoPin, INPUT);

  servo.attach(17);               //attach servo to pin 17
  servo.write(90);
  
  turnSensorSetup();
  
}


void loop()
{

//state machine switch case 

  switch(state)
  {
    case Idle:
      idleState();
      break;

    case CalibrateStraight:
      calibrateStraightState();
      break;

    case Straight:
      straightState();
      if (isObject()) { state = Turn; }
      break;

    case Turn:
      turnState();
      if (!isObject()) { state = Straight;  }
      break;  

  }
  if (buttonC.isPressed()) {
      stopMotors();
      state = Idle;
  }
}

//Returns angle in degrees
int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

 }
 
//Path Finding Methods 

  //reads values from Ultrasonic sensor, returns a distance in centimeters
      int readUltraSonicSensor()
      {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(5);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
      
        pinMode(echoPin, INPUT);
        duration = pulseIn(echoPin, HIGH);
        
        cm = (duration/2) / 29.1;
      
        return cm;
      }

  //Turns servo a to a specified position in degrees
      void servoTurn(int angle)
      { 
        servo.write(angle);
      }

  //Finds path with the greatest distance
      int findLongestPath() {
        
        longestDist = 1;
        
        for(int angle = 0; angle <= 180; angle += 10) {
          
          servoTurn(angle);
          currentDist = readUltraSonicSensor();
      
          if (currentDist > longestDist && currentDist < 1100) {
            longestDist = currentDist; 
            longestDirection = angle;
            //Serial.println("Greater Distance found");
          }
          
          //Serial.println(currentDist);
          //Serial.println(longestDist);
          
          delay(75);
      
        }
        longestDirection;
        return longestDirection; 
      }

/*Reads the value from the front two sensors and returns true or false
     *true : if front sensors read 6 or greater
    */
bool isObject() {

    /*Removed side proxSensors to just deal with front sensors */

    
    proxSensors.read();
    if (proxSensors.countsFrontWithLeftLeds() >= 10 || proxSensors.countsFrontWithRightLeds() >= 10){
      return true; 
    } else {
      return false;
    }
  
  }
  

//Function to stop the motors when called
void stopMotors() {
  motors.setSpeeds(0, 0);
  }

//reads and corrects motor values using PID control 
void correctMotorValues(){
  
    //reads encoders every 100 ms
  if ((millis() - previousTime) >= 100)
  {
    double currentTime = millis();
    double elapsedTime = (currentTime - previousTime);
    
    int16_t countsLeft = encoders.getCountsAndResetLeft();
    int16_t countsRight = encoders.getCountsAndResetRight();

    int error = countsRight - countsLeft;
    totalError += error * elapsedTime;
    derivError = (error-lastError) / elapsedTime;
    
    //Uses PID control to adjust the speed
        int speedDifference = (Kp * error) + (Ki * totalError) + (Kd * derivError);
        lastError = error;

    //If the speed difference is positive, the right motor is going faster than the left.
        //This means that the right motor speed will be decreased by the speed difference.
         int leftSpeed = (int)maxSpeed - speedDifference;
         int rightSpeed = (int)maxSpeed + speedDifference;

    //The contrain function will instill a domain for the speed - it has to be
        // >= 0 and <= maxSpeed. This function will fix that.
        leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
        rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);

        motors.setSpeeds(leftSpeed, rightSpeed);
      
        previousTime = currentTime;
    
  }
  
}

/*     
      
        //If the speed difference is positive, the right motor is going faster than the left.
        //This means that the right motor speed will be decreased by the speed difference.
         leftSpeed = (int)maxSpeed - speedDifference;
         rightSpeed = (int)maxSpeed + speedDifference;
      
        //The contrain function will instill a domain for the speed - it has to be
        // >= 0 and <= maxSpeed. This function will fix that.
        leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
        rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);
      
        motors.setSpeeds(leftSpeed, rightSpeed);
      
        previousTime = currentTime;
      }*/

//States for state machine 
    //Idle State
      void idleState()
      {
      
        if (buttonA.isPressed()) {
          state = CalibrateStraight;
        }
      }
      
    // Straight Calibration State
      void calibrateStraightState()
      {
        /*Set up gyroscope*/
        turnSensorSetup();
       
        buttonA.waitForButton(); // Wait for button A to be pressed to start
        
        // Buzzer variables in case they need to be changed
        unsigned int buzzerFrequency = 261; // Middle C
        unsigned int buzzerDuration =  400; // In milliseconds
        unsigned char buzzerVolume = 10; // On scale of 0-15
        
      
        for (int x = 0; x <= 2; x++) {
          buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer 3 times 
        }
        delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A
        lastEncoderTime = millis(); //sets initial value
        proxSensors.initThreeSensors(); // configures proxSensors to use all three sensors
        if(isObject()) 
        {
          state = Turn; 
        } 
        else 
        {
          state = Straight;
        }
      }
      
      
    // Straight State
      void straightState()
      {
          motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Run motors at specified speeds
          delay(50);
          correctMotorValues();//read encoder data to correct trajectory
          
      }
      
    // Turn State
      void turnState()
      {
        motors.setSpeeds(0,0);
        pathCorrect = findLongestPath();
              turnSensorUpdate();
              /*turns the bot until the gyroscope matches the direction of the longest path */
              if (pathCorrect > 90) {
                 while(getAngle() < pathCorrect - 90) {
                  motors.setSpeeds(-motorSpeedLeft, motorSpeedRight);
                 }
              }
              else if (pathCorrect < 90) {
                while(abs(getAngle()) < pathCorrect) {
                  motors.setSpeeds(motorSpeedLeft, -motorSpeedRight);
                }
              }
              else {
                  motors.setSpeeds(0, 0);
              }
          turnSensorReset(); //Reset gyroscope 
      }
