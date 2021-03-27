#ifndef ENCODERDISTANCE_H
#define ENCODERDISTANCE_H



#include <Wire.h>
#include <Zumo32U4.h>
#include <iostream>

class encoderDistance{
    private:
        unsigned long distance;
        int16_t encoder;
        
    public:
        encoderDistance();
        encoderDistance(int16_t);

        /*getter methods for distance values (cm and in) */
        unsigned long getDistance() const;
        
        /*setters methods for distance values*/
        void setDistance();
        

};

#include "encoderDistance.cpp"

#endif