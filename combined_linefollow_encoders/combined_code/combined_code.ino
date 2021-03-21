/*  ORGANIZATION: Pitt-RAS
 *  AUTHORS:      Killian Rush, Mark Hofmeister, Morgan Visnesky
 *  DATE:         3/20/2021
 *  DESCRIPTION:
 *    Combination of straight line encoder and linefollow code
 */

#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"

const uint16_t maxSpeed = 200;

Zumo32U4IMU imu;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;

float Kp = 0.4; // Proportional Term
float Kd = 9; // Derivative Term
float Ki = 0; // Integral Term

double lastError = 0; // Error from last sensor reading.
double totalError = 0; // Accumulated error.
double derivError; // Derivative of error taken over the last time step

double previousTime = 0;
double elapsedTime;

#define numSensors 5
unsigned int lineSensorValues[numSensors];
int leftSpeed = 0, rightSpeed = 0;

// Initial speeds for left and right motors (0-400)
int16_t motorSpeedLeft  = 100;
int16_t motorSpeedRight = 100;

unsigned long initialDelay = 1000;

//declare for use in encoder adjustment
unsigned long int lastEncoderTime;

int option = 0;

//Necessary to calibrate for the environment
void calibrateSensors()
{
  lcd.clear();
  delay(1000);
  for(int i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }
    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

void setup()
{
  
  if (option == 1)
  {
    //motors.flipLeftMotor(true);
    //motors.flipRightMotor(true);
  
    //Initialized sensors
    lineSensors.initFiveSensors();
  
    //Calibration loop
    lcd.clear();
    lcd.print(F("Press A"));
    lcd.gotoXY(0, 1);
    lcd.print(F("to calibrate"));
    buttonA.waitForButton();
  
    //Spins robt around to expose it to an environment of variable refelectance
    calibrateSensors();
  
    //Press A to Go
    lcd.clear();
    lcd.print(F("Press A"));
    lcd.gotoXY(0,1);
    lcd.print(F("to begin"));
    buttonA.waitForButton();
  
    delay(500);
    lcd.clear();
    lcd.print(F("Operating"));
  }
  else
  {
    /*Set up gyroscope*/
    turnSensorSetup(); 
    buttonA.waitForButton(); // Wait for button A to be pressed to start
    
    // Buzzer variables in case they need to be changed
    unsigned int buzzerFrequency = 261; // Middle C
    unsigned int buzzerDuration =  50; // In milliseconds
    unsigned char buzzerVolume = 10; // On scale of 0-15
    
    
    buzzer.playFrequency(buzzerFrequency, buzzerDuration, buzzerVolume); // Play buzzer
    delay(initialDelay); // Delay robot so it doesn't immediately move after pressing button A
    lastEncoderTime = millis(); //sets initial value
    proxSensors.initThreeSensors(); // configures proxSensors to use all three sensors
  }
}

void loop()
{
  if (option == 1)
  {
    double currentTime = millis();
    elapsedTime = (currentTime - previousTime);
  
    //Reads the line sensor values. If there is no error, and a black
    //line is detected, position will be 2000.
    int position = lineSensors.readLine(lineSensorValues);
  
    // 2000 means that the black line is directly below sensor #2 of the 5 sensor array.
    // sensors = [0 1 2 3 4], values = [0 1000 2000 3000 4000]
    // So when position reads 0 the black line is under sensor 0,
    // when position reads 4000 it is under sensor 4.
  
    int error = 2000 - position;
    totalError += error * elapsedTime;
    derivError = (error-lastError) / elapsedTime;
  
    //Uses PID control to adjust the speed
    int speedDifference = (Kp * error) + (Ki * totalError) + (Kd * derivError);
    lastError = error;
  
    //If the speed difference is positive, the right motor is going faster than the left.
    //This means that the right motor speed will be decreased by the speed difference.
     leftSpeed = (int)maxSpeed - speedDifference;
     rightSpeed = (int)maxSpeed + speedDifference;
  
    //The contrain function will instill a domain for the speed - it has to be
    // >= 0 and <= maxSpeed. This function will fix that.
    leftSpeed = constrain(leftSpeed, 0, (int)maxSpeed);
    rightSpeed = constrain(rightSpeed, 0, (int)maxSpeed);
  
    motors.setSpeeds(leftSpeed, rightSpeed);
    //Serial.print(position);
  
    previousTime = currentTime;
    if (buttonC.isPressed()) {
        motors.setSpeeds(0,0);
        exit(0);
    }
  }
  else
  {
   /*conditional statement 
   *if we detect object we stop and turn else the bot moves forward*/
    if(isObject()) {
        turn(); 
      } else {
        motors.setSpeeds(motorSpeedLeft, motorSpeedRight); // Run motors at specified speeds
        readMotorValues();//read encoder data to correct trajectory
        }
  }

/*Fucntion to stop the motors when called*/
void stopMotors() {
  motors.setSpeeds(0, 0);
  }


bool isObject() {

    /*Removed side proxSensors to just deal with front sensors (for now)*/

    /*Reads the value from the front two sensors and returns true or false
     *true : if front sensors read 6 or greater
    */
    proxSensors.read();
    if (proxSensors.countsFrontWithLeftLeds() >= 6 || proxSensors.countsFrontWithRightLeds() >= 6){
      return true; 
    } else {
      return false;
    }
  
  }


void turn(){
  
    //turnSensorUpdate();
    
    while(1){
      turnSensorUpdate();
      /*turns the bot until the gyroscope reads an angle of 35 degrees*/
      if(getAngle()<35 && getAngle()>0 ) {
          motors.setSpeeds(-motorSpeedLeft, motorSpeedRight); 
        } else if(getAngle()>-35 && getAngle()< 0 ) {
          motors.setSpeeds(motorSpeedLeft, -motorSpeedRight); 
        } else {
          motors.setSpeeds(0,0); 
          break;
          }
      }  
      turnSensorReset(); //Reset gyroscope 
  
}


/*Displays motors onto LCD*/
void readMotorValues(){
    //reads encoders and adjusts speeds every 100 ms
  if ((millis() - lastEncoderTime) >= 100)
  {
    lastEncoderTime = millis();
    int16_t countsLeft = encoders.getCountsAndResetLeft();
    int16_t countsRight = encoders.getCountsAndResetRight();

    /*adjusts speed based on encoder data*/
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

    /*Removed CR and CL since string length is interfering with LCD display capacity*/
    /* update LCD screen*/
    lcd.clear();  // clears screen
    lcd.gotoXY(0,0); // sets position to line 
    lcd.print(countsLeft); // displays the countsLeft encoder
    lcd.gotoXY(0,1);
    lcd.print(countsRight);// displays the countsRight encoder
  }
}


/*function returns the turn angle read from the gyroscope in degrees*/
int32_t getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

 }
