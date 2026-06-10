#include <Arduino.h>
#include <inputs_interface.h>

#include <motors.h>

MOTOR leftMotor(3, 4);
MOTOR rightMotor(5, 6);

void setup()
{
    PS4::DATA::init();
    leftMotor.begin();
    rightMotor.begin();

    Serial.println("Waiting for controller...");
    bool state = false;
    while (!PS4::poll())
    {
        delay(400);
        digitalWrite(LED_BUILTIN, state);
        state = !state;
    }
    Serial.println("Controller Connected!");
}

void loop()
{
    PS4::poll();
    // Simple tank drive logic
    int y = PS4::LStickY() * 2;
    int x = PS4::LStickX() * 2;

    leftMotor.setPower(y + x);
    rightMotor.setPower(y - x);
}
