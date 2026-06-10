#pragma once
#include <Arduino.h>

class MOTOR
{
public: // settings
    const static int MAX_SPEED = 255;

private:
    uint8_t pwm;
    uint8_t dir;
    int8_t invertMultiplier;

public:
    MOTOR(int pwm, int dir, bool invert);
    MOTOR(int pwm, int dir);
    void begin();
    // set motor power from -255 to 255. Make sure you map your inputs!
    void setPower(int targetPower);
    // manually set pwm pin from 0 to 255 and dir pin as a boolean
    void setPins(uint8_t pwm, bool dir);
    // set-and-forget motor inversion, will apply to every function EXCEPT setPins
    void setMotorInvert(bool invert);
};
