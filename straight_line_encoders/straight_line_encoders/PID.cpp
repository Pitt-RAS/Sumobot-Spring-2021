#include "Arduino.h"
#include "PID.h"

//Set all K values and reset error and timing fields
void PID::setPID(float Kp_new, float Ki_new, float Kd_new)
{
	//Update K values
	Kp = Kp_new;
	Ki = Ki_new;
	Kd = Kd_new;

	// Initialize lastTime, Ei, and lastEp
	lastTime = millis();
	Ei = 0;
	lastEp = 0;
}

// use the PID controller to generate a control signal by sending the controller
// a desired set_point and the current feedback state of the system
float PID::error_correction(float set_point, float input)
{
	// determine time elapsed since last error calculation and update lastTime
	unsigned long currentTime = millis();
	unsigned long elapsedTime = currentTime - lastTime;
	lastTime = currentTime;

	// error calculations
	Ep = set_point - input;
	Ei += Ep * elapsedTime;
	Ed = (Ep - lastEp) / elapsedTime;
	lastEp = Ep;

	// calculate output and return
	return Kp * Ep + Ki * Ei + Kd * Ed;
}
