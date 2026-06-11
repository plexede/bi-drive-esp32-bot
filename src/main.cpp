#include <Arduino.h>
#include <inputs_interface.h>
#include <PS4Controller.h>

#include <motor.h>

MOTOR leftMotor(34, 35);
MOTOR rightMotor(32, 33);

void setup()
{
    pinMode(2, OUTPUT); // builtin led
    Serial.begin(115200);
    Serial.println("boot");

    bool isInit_BT;
    isInit_BT = inputs_interface::init();

    if (!isInit_BT)
    {
        bool ledState = true;
        while (1)
        {
            Serial.println("FATAL: Bluetooth init failed.");
            digitalWrite(2, ledState);
            ledState = !ledState;
            delay(1000);
        }
    }

    // initialize motors
    leftMotor.begin();
    rightMotor.begin();
}

void loop()
{
    // Check for new inputs
    if (inputs_interface::inputsReady)
    {
        inputs_interface::inputsReady = false;
        digitalWrite(2, PS4.PSButton() ? HIGH : LOW);

        // Simple tank drive logic
        int y = inputs_interface::filterDeadzone(PS4.LStickY(), 4) * 2;
        int x = inputs_interface::filterDeadzone(PS4.LStickX(), 4) * 2;

        leftMotor.setPower(y + x);
        rightMotor.setPower(y - x);
    }
}
