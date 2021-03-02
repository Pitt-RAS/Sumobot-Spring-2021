#ifndef PID_h
#define PID_h

class PID
{
    float Kp;
    float Ki;
    float Kd;
    unsigned long t;
    float Ep;
    float Ei;
    float Ed;

  public:
    float error_correction(float set_point, float input);
    void setPID(float Kp_new, float Ki_new, float Kd_new);

};

#endif