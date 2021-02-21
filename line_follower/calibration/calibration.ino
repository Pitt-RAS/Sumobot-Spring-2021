/*  ORGANIZATION: Pitt-RAS
 *  AUTHORS:      Mark Hofmeister, Morgan Visnesky
 *  DATE:         12/21/2020
 *  FILENAME:     calibration.ino
 *  DESCRIPTION:
 *    Calibration function
 */


// This file has been modified
#include <Wire.h>
#include <Zumo32U4.h>


const uint16_t maxSpeed = 200;

Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonC buttonC;


#define numSensors 5
unsigned int lineSensorValues[numSensors];
int leftSpeed = 0, rightSpeed = 0;

//Necessary to calibrate for the environment
void calibrateSensors()
{
  lcd.clear();
  delay(1000);
  for(int i = 0; i < 150; i++)
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

void loop()
{
}
