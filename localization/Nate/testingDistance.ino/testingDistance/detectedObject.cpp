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
detectedObject::detectedObject(float dist) {
    xAxis = dist; 
    yAxis = 0; 
    distanceFromBot = dist; 
}


/**
 * @return : distance calculated by the bot from the object.
 * 
*/
float detectedObject::getDistance() {return distanceFromBot;}

int32_t detectedObject::getBotAngle() {return angle;}

/** Accepts data from the encoder and converts it into distance of centimeters
 *  909.7 counts per rotation
 *  sprocket + track ~ 1.5in or 3.81 cm (diameter)
 *  circumference 
 * @param : 16 bit int from that accepts data from encoders
 * @return: distance from the encoder 
*/
float detectedObject::convert(int16_t data) {
    return (data/909.7)*(sprocketCirc); 
}

/**
 * Update the distance of this instance of the object everytime the bot moves
 * 
 * @param : takes input from the encoders as CPR
*/
void detectedObject::updateDistance(int16_t data, int32_t angle) {
    this -> angle = angle; 
    xAxis = convert(data)*cos(angle); 
    yAxis = convert(data)*sin(angle); 
    distanceFromBot = sqrt(pow(xAxis, 2) + pow(yAxis, 2));
}
