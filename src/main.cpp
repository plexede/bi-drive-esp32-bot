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
        int y = myController->axisY();
        int x = myController->axisRX();

        if (abs(y) < 10) y = 0;
        if (abs(x) < 10) x = 0;

        drive(constrain(y + x, -255, 255), constrain(y - x, -255, 255));
    } else {
        stopMotors();
    }
}
