#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H
#include <math.h> 
#include "TurnSensor.h"


class detectedObject {
    private:
        unsigned long distanceFromBot;
        long xAxis, yAxis, angle; 
        

    public:
        detectedObject();
        detectedObject(long);
        unsigned long getDistance() const; 
        long convert(int16_t);
        int32_t getBotAngle(); 
        void update(int16_t); 
        

}; 

#endif