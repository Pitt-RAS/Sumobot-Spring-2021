#ifndef ENCODERDISTANCE_H
#define ENCODERDISTANCE_H



#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include <iostream>
#include <stdint.h>

class encoderDistance{
    private:
        unsigned long distance;
        int16_t encoder;

        int32_t getAngle();
        int32_t turnAround();
        
    public:
        encoderDistance();
        encoderDistance(int16_t);

        /* getter methods for distance values (cm) */
        unsigned long getDistance() const;
        
        /* setters methods for distance values */
        void setDistance();

        /* returns bot to its original position */
        /* only works in a straight line for now */
        void returnToOrigin();

        

};

#include "encoderDistance.cpp"

#endif