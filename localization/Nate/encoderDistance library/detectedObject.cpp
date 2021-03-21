// class detectedObject {
//     public:
//         unsigned long distanceFromBot;
//         long xAxis, yAxis, angle; 

//     private:
//         detectedObject();
//         void update(); 
        

// }; 
        

#include "Zumo32U4Encoders.h"
#include "detectedObject.h"
#include <cmath> 
#include <vector> 

/**
 * Default Constructor
 * 
 * @def : Sets the ORIGIN of where the bot detected the object 
*/
detectedObject::detectedObject() {
    xAxis = 0; 
    yAxis = 0; 
    distanceFromBot = sqrt(pow(cos(xAxis)) + pow(sin(yAxis))); 
}

/**
 * Overloaded Constructor
 * 
 * @param long : initial distance based on the reading of the IR sensors
 * @def : sets the of the ojbect from the bot to be SOLELY on the x-axis  ( for testing )
 * 
 * */
detectedObject::detectedObject(long dist) {
    xAxis = dist; 
    yAxis = 0; 
    distanceFromBot = sqrt(pow(cos(xAxis)) + pow(sin(yAxis))); 
}

unsigned long detectedObject::convert() {



}