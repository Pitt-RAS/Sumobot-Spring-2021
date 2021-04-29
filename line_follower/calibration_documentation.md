# Calibration

This is a documentation for the calibration that will be used on our SumoBot.

## What is calibration?

Calibration is the process used to set measurements for an instrument to determine whether the sensor can read data values and convert them to digital signals. This will also allow the devices to adapt to their environments providing data that would be considered reasonable.

## The method

void calibrateSensors()
Bot turns one direction for a certain amount of iterations while calibrating, and then calibrates in the other direction for the remaining sets of iterations. After calibration, the motors are killed.

void setup()
Firstly, all sensors must be initialized. User then presses A button to commence calibration which calls the calibrateSensors() function. Then user can press A again to start motors running.