#include <Arduino.h>
#include <inputs_interface.h>

#include <motors.h>

void setup()
{
    PS4::DATA::init();


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
    BLE.poll();
}
