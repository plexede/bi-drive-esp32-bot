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

void drive(int left, int right) {
    digitalWrite(leftDir, left >= 0 ? HIGH : LOW);
    digitalWrite(rightDir, right >= 0 ? HIGH : LOW);
    analogWrite(leftPWM, abs(left));
    analogWrite(rightPWM, abs(right));
}

void setup() {
    pinMode(leftPWM, OUTPUT); pinMode(leftDir, OUTPUT);
    pinMode(rightPWM, OUTPUT); pinMode(rightDir, OUTPUT);
    
    if (!BLE.begin()) {
        while (1);
    }
}

void loop() {
    // Note: ArduinoBLE implementation for PS4 controller 
    // requires specific HID profile handling.
    // This is a placeholder for your BLE logic.
    BLE.poll();
}
