#include <Arduino.h>
#include <inputs_interface.h>

#include <motor.h>

MOTOR leftMotor(34, 35);
MOTOR rightMotor(32, 33);

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
    // Check for new inputs
    PS4::poll();
    // Status light
    digitalWrite(LED_BUILTIN, PS4::PSButton());

    // Simple tank drive logic
    int y = PS4::LStickY() * 2;
    int x = PS4::LStickX() * 2;

    leftMotor.setPower(y + x);
    rightMotor.setPower(y - x);
}
