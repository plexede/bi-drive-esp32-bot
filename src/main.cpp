#include <Arduino.h>
#include <ArduinoBLE.h>

// Pin Definitions
const int leftPWM = 3;
const int leftDir = 4;
const int rightPWM = 5;
const int rightDir = 6;

void stopMotors() {
    analogWrite(leftPWM, 0);
    analogWrite(rightPWM, 0);
}

// Weight system constants
const float PRECISION_MODE = 0.3;
const float NORMAL_MODE = 0.6;
const float TURBO_MODE = 1.0;

float speedMultiplier = NORMAL_MODE;

void drive(int left, int right) {
    // Apply normalized weight
    int weightedLeft = (int)(left * speedMultiplier);
    int weightedRight = (int)(right * speedMultiplier);

    digitalWrite(leftDir, weightedLeft >= 0 ? HIGH : LOW);
    digitalWrite(rightDir, weightedRight >= 0 ? HIGH : LOW);
    analogWrite(leftPWM, abs(weightedLeft));
    analogWrite(rightPWM, abs(weightedRight));
}

void setup() {
    pinMode(leftPWM, OUTPUT); pinMode(leftDir, OUTPUT);
    pinMode(rightPWM, OUTPUT); pinMode(rightDir, OUTPUT);
    
    if (!BLE.begin()) {
        while (1);
    }
}

void loop() {
    BLE.poll();
}
