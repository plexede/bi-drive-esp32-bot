#include <Arduino.h>
#include <PS4Controller.h>

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
    
    // Replace with your PS4 controller MAC address
    PS4.begin("00:00:00:00:00:00"); 
}

void loop() {
    if (PS4.isConnected()) {
        int y = PS4.data.analog.stick.ly; // Forward/Backward
        int x = PS4.data.analog.stick.rx; // Turn

        // Apply deadzone
        if (abs(y) < 10) y = 0;
        if (abs(x) < 10) x = 0;

        // Differential drive mixing
        int leftSpeed = y + x;
        int rightSpeed = y - x;

        drive(constrain(leftSpeed, -255, 255), constrain(rightSpeed, -255, 255));
    } else {
        stopMotors();
    }
}
