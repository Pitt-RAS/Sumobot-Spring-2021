#include "Arduino.h"
#include "PID.h"

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
	return kp * Ep + ki * Ei + kd * Ed;
}

//Set all K values
void PID::setPID(float Kp_new, float Ki_new, float Kd_new)
{
	//Update K values
	Kp = Kp_new;
	Ki = Ki_new;
	Kd = Kd_new;
}
