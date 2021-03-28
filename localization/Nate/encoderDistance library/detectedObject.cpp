#include "detectedObject.h"  

/**
 * Default Constructor
 * @def : Sets the ORIGIN at the bots location 
*/
detectedObject::detectedObject() {
    xAxis = 0; 
    yAxis = 0; 
    distanceFromBot = 0; 
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
    distanceFromBot = dist; 
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
long detectedObject::convert(int16_t data) {
    return (data/909.7)*(3.81); 
}

/**
 * Update the distance of this instance of the object everytime the bot moves
 * 
 * @param : takes input from the encoders as CPR
*/
void detectedObject::update(int16_t data) {
    angle += getBotAngle(); 
    xAxis += convert(data)*cos(angle); 
    yAxis += convert(data)*sin(angle); 
    distanceFromBot = sqrt(pow(xAxis, 2) + pow(yAxis, 2));
}

/*function returns the turn angle read from the gyroscope in degrees*/
int32_t detectedObject::getBotAngle() {
    return (((int32_t)turnAngle >> 16)*360)>>16; 
 }