#include "encoderDistance.h"
#include <stdint.h>

encoderDistance::encoderDistance(){
    encoder = 0;
}
encoderDistance::encoderDistance(int16_t encoder){
    this -> encoder;
}
unsigned long encoderDistance::getDistance() const{
    return distance;
}

void encoderDistance::setDistance(){
    distance = (encoder/909.7)*3.81;
}

void encoderDistance::returnToOrigin(){
    turnAround();
    int16_t originEncoder = (getDistance()/3.81)*909.7;
    //motors.encoder(originEncoder)

}

int32_t encoderDistance::getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

}

void encoderDistance::turnAround(){
    Zumo32U4Motors motors;

    int16_t motorSetSpeedLeft = 200;
    int16_t motorSetSpeedRight = 200;

    while(1){
        turnSensorUpdate();
        if(getAngle() < 180 && getAngle() > 0){
            motors.setSpeeds(-motorSetSpeedLeft, motorSetSpeedRight);
        } else if (getAngle() < 0 && getAngle() > -180)
        {
            motors.setSpeeds(motorSetSpeedLeft, -motorSetSpeedRight);
        } else{
            motors.setSpeeds(0,0);
            break;
        }
    }

    turnSensorReset();
    
}