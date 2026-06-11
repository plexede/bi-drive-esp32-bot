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
    // helper to clamp values between -255 and 255
    int clamp(int value);
    // set-and-forget motor inversion
    void setMotorInvert(bool invert);
};
