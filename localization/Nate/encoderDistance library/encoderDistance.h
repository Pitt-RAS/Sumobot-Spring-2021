#ifndef ENCODERDISTANCE_H
#define ENCDOERDISTANCE_H


#include "Zumo32U4Encoders.h"

class encoderDistance {
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