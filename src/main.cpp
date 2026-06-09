#include <Arduino.h>
#include <Bluepad32.h>

// Pin Definitions
const int leftPWM = 3;
const int leftDir = 4;
const int rightPWM = 5;
const int rightDir = 6;

ControllerPtr myController = nullptr;

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

void onConnectedController(ControllerPtr ctl) {
    myController = ctl;
}

void onDisconnectedController(ControllerPtr ctl) {
    myController = nullptr;
    stopMotors();
}

void setup() {
    pinMode(leftPWM, OUTPUT); pinMode(leftDir, OUTPUT);
    pinMode(rightPWM, OUTPUT); pinMode(rightDir, OUTPUT);
    
    BP32.setup(&onConnectedController, &onDisconnectedController);
}

void loop() {
    BP32.update();

    if (myController && myController->isConnected()) {
        int y = myController->axisY(); // Forward/Backward
        int x = myController->axisRX(); // Turn

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
