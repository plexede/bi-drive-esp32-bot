#include <Arduino.h>
#include "motors.h"

const int leftPWM = 3;
const int leftDir = 4;
const int rightPWM = 5;
const int rightDir = 6;

const float NORMAL_MODE = 0.6;
float speedMultiplier = NORMAL_MODE;

void stopMotors()
{
    analogWrite(leftPWM, 0);
    analogWrite(rightPWM, 0);
}

void drive(int left, int right)
{
    int weightedLeft = (int)(left * speedMultiplier);
    int weightedRight = (int)(right * speedMultiplier);

    digitalWrite(leftDir, weightedLeft >= 0 ? HIGH : LOW);
    digitalWrite(rightDir, weightedRight >= 0 ? HIGH : LOW);
    analogWrite(leftPWM, abs(weightedLeft));
    analogWrite(rightPWM, abs(weightedRight));
}
