/*
 File:		PID.h
 Created:	3/1/2021
 Updated:   3/6/2021
 Author:	Ethan Markowski, Hudson Panning, Brian Randall
 
 Purpose:   PID controller library
*/

#ifndef PID_h
#define PID_h

#include "Arduino.h"

class PID
{
    float Kp;
    float Ki;
    float Kd;
    unsigned long lastTime;
    float Ep;
    float Ei;
    float Ed;
    float lastEp;

  public:
      // Set all K values and reset error and timing fields
      // ** The error_correction method should not be used without first calling setPID
      // ** If the robot is sitting in a paused state, setPID should be used on resume to reset the PID object's timer
      // Failing to do this could result in an arbitrarily large amount of integral error being stored on the
      // control loop following the exit from the paused state
      void setPID(float Kp_new, float Ki_new, float Kd_new);

      // Calling error_correction uses the PID object to generate a control signal by sending the controller a desired
      // set_point and the current feedback state of the system
      float error_correction(float set_point, float input);
};

#endif