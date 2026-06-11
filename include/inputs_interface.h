#pragma once
#include <Arduino.h>
/*
Available Inputs:
Buttons: Cross, Circle, Square, Triangle, Up, Down, Left, Right, PSButton, Touchpad, Share, Options, L1, R1, L3, R3
Analog: LStickX, LStickY, RStickX, RStickY, L2, R2
Status: battery, charging, audio, mic
Sensors: gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z
*/
namespace inputs_interface
{
    extern bool inputsReady;
    bool init();
}