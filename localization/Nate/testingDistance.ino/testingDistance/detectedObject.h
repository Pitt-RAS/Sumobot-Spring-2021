#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H
#include <math.h> 
#include "TurnSensor.h"

  

class detectedObject {
    private:
        float distanceFromBot;
        float xAxis, yAxis;
        int32_t angle; 
        const float sprocketCirc = 2*M_PI*(3.7/2);

    public:
        detectedObject();
        detectedObject(float);
        float getDistance(); 
        int32_t getBotAngle(); 
        float convert(int16_t); 
        void updateDistance(int16_t, int32_t); 
        

}; 

#endif
