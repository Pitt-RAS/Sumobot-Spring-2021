#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H



#include <Wire.h>
#include <Zumo32U4.h>

class detectedObject {
    public:
        unsigned long distanceCentimeters;
        
    private:
        encoderDistance();
        encoderDistance(int16_t);

        /*getter methods for distance values (cm and in) */
        unsigned long getDistanceCentimeters() const;
        
        /*setters methods for distance values*/
        void setDistanceCentimeters();
        

}; 

#endif