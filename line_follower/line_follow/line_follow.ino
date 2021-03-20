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

void fakePID(pos)
{
  int returnValues[2];
  if (pos > 0)
  {
    returnValues[0]=200;
    returnValues[1]=-200;
  }
  else
  {
    returnValues[0]=-200;
    returnValues[1]=200;
  }
  return returnValues;
}



void setup()
{
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);

  //Initialized sensors
  lineSensors.initFiveSensors();

  //Spins robt around to expose it to an environment of variable refelectance
  calibrateSensors();
  
  delay(500);
}

void loop()
{
  //Determines position of line with respect to robot. readLine returns 0 if directly below sensor 0, 1000 if below sensor 1, etc until 5.
  int sensorValue = lineSensors.readLine();
  int pos = 2500 - sensorValue;

  //fakePID will be replaced with actual PID when finished.
  motorSpeeds = fakePID(pos);
  motors.setSpeeds(motorSpeeds[0], motorSpeeds[1]);
}
