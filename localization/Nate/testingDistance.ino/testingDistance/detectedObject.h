#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H
#include <math.h> 
#include <stdint.h> 


class detectedObject {
    private:
        unsigned long distanceFromBot;
        long xAxis, yAxis, angle; 
        

    public:
        detectedObject();
        detectedObject(long);
        unsigned long getDistance() const; 
        unsigned long convert(int16_t);

}; 

#endif
