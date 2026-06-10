#include "motor.h"

MOTOR::MOTOR(int pwm, int dir, bool invert)
{
    this->pwm = pwm;
    this->dir = dir;
    this->invertMultiplier = invert ? -1 : 1;
}

MOTOR::MOTOR(int pwm, int dir)
{
    this->pwm = pwm;
    this->dir = dir;
    invertMultiplier = 1;
}

void MOTOR::begin()
{
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
}

void MOTOR::setPower(int _targetPower)
{
    int power = constrain(_targetPower, -MAX_SPEED, MAX_SPEED);
    power *= invertMultiplier;
    bool direction = power > 0;
    uint8_t pwmPower = map(abs(power), 0, MAX_SPEED, 0, 255);
    if (abs(_targetPower) > MAX_SPEED)
    {
        Serial.println("Motor power rollover. Did you mean to do that?");
    }

    analogWrite(pwm, pwmPower);
    digitalWrite(dir, direction);
}

