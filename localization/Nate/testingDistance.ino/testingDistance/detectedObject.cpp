#include "detectedObject.h"  

/**
 * Default Constructor
 * @def : Sets the ORIGIN at the bots location 
*/
detectedObject::detectedObject() {
    xAxis = 0; 
    yAxis = 0; 
    distanceFromBot = sqrt(pow(xAxis, 2) + pow(yAxis, 2)); 
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
    distanceFromBot = sqrt(pow(xAxis, 2) + pow(yAxis, 2)); 
}


/**
 * @return : distance calculated by the bot from the object.
 * 
*/
unsigned long detectedObject::getDistance() const {return distanceFromBot;}

/** Accepts data from the encoder and converts it into distance of centimeters
 *  909.7 counts per rotation
 *  sprocket + track ~ 1.5in or 3.81 cm (diameter)
 *  circumference 
 * @param : 16 bit int from that accepts data from encoders
 * @return: distance from the encoder 
*/
unsigned long detectedObject::convert(int16_t data) {
    return (data/909.7)*(2*M_PI*(3.7/2)); 
}
