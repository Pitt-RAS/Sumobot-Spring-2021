#include "encoderDistance.h"

unsigned long encoderDistance::getDistance() const{
    return distance;
}

void encoderDistance::setDistance(){
    distance = (encoder/909.7)*12;
}