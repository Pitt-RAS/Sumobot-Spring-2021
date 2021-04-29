Definition of Zumo32U4LineSensors Source: <br />
https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html <br />
Inherits QTRSensorsRC: <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors_r_c.html <br />
Inherits QTRSensors: <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors.html <br /> <br />

Public Functions: <br />
readCalibrated(sensor_values) <br />
Populates sensor_values with the values of each sensor output between 0 and 1000. 0 Corresponds with the minimum value read by sensor during calibrate and 1000 the max. These min and max are stored separately for each sensor. <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors.html#aa32a448ac03cd2a45d1f14f96ac4b739 <br /><br />

calibrate() <br />
Identifies the minimum and maximum values each line sensor detects and stores them in the sensor. <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors.html#ac9840e2429c7a962977057ba154c77da <br /> <br />

resetCalibration() <br />
Resets the min and max the sensor has read, allowing for new min and max values to be detected for linesensors.calibrate(). <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors.html#aa840b6ef17562d41edf21ddd08e0672e <br /> <br />

readLine() <br />
Returns an estimated position (see full math in link) <br />
https://pololu.github.io/zumo-shield-arduino-library/class_q_t_r_sensors.html#ac84f0b98bceae0b59d687ae82eb92718 <br /> <br />

initThreeSensors() <br />
Initializes the robot to use 3 sensors: sensor 1, 3, and 5. <br />
https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html#a880737a0df457e9acf3277b2342e4087 <br /><br />

initFiveSensors() <br />
Initialized the robot to use all 5 sensors. <br />
https://pololu.github.io/zumo-32u4-arduino-library/class_zumo32_u4_line_sensors.html#a3873997ed35fbc1c6c57411f6cee1f2d <br /> <br />
