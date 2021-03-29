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
    //turnAround
    int16_t originEncoder = (getDistance()/3.81)*909.7;
    //motors.encoder(originEncoder)

}

int32_t encoderDistance::getAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 

}

int32_t encoderDistance::turnAround(){
    Zumo32U4Motors motors;

    int16_t motorSetSpeedLeft = 200;
    int16_t motorSetSpeedRight = 200;

    if(getAngle() < )
}