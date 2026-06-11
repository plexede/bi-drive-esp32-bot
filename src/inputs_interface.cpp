#include "inputs_interface.h"
#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

#define DEADZONE 4 // TODO: adjust this!

namespace PS42
{

    // abstracted for ease of access

    /*********************/
    /*   B U T T O N S   */
    /*********************/

    bool Cross() { return PS4.Cross(); }
    bool Circle() { return PS4.Circle(); }
    bool Square() { return PS4.Square(); }
    bool Triangle() { return PS4.Triangle(); }

    bool Up() { return PS4.Up(); }
    bool Down() { return PS4.Down(); }
    bool Left() { return PS4.Left(); }
    bool Right() { return PS4.Right(); }

    bool PSButton() { return PS4.PSButton(); }
    bool Touchpad() { return PS4.Touchpad(); }
    bool Share() { return PS4.Share(); }
    bool Options() { return PS4.Options(); }

    bool L1() { return PS4.L1(); }
    int8_t L2() { return PS4.L2(); }

    bool R1() { return PS4.R1(); }
    int8_t R2() { return PS4.R2(); }

    bool R3() { return PS4.R3(); }
    bool L3() { return PS4.L3(); }

    /********************/
    /*    A N A L O G   */
    /********************/

    int filterDeadzone(int _input, int _deadZone)
    {
        if (_input > _deadZone || _input < -_deadZone)
        {
            return _input;
        }
        return 0;
    }

    int8_t LStickX()
    {
        return filterDeadzone(PS4.LStickX(), DEADZONE);
    }

    int8_t LStickY()
    {
        return filterDeadzone(PS4.LStickY(), DEADZONE);
    }

    int8_t RStickX()
    {
        return filterDeadzone(PS4.RStickX(), DEADZONE);
    }

    int8_t RStickY()
    {
        return filterDeadzone(PS4.RStickY(), DEADZONE);
    }

    /*******************************/
    /*   S T A T U S   F L A G S   */
    /*******************************/
    uint8_t battery() { return PS4.battery(); }
    bool isCharging() { return PS4.charging(); }
    bool hasAudio() { return PS4.audio(); }
    bool hasMic() { return PS4.mic(); }

    /********************/
    /*   S E N S O R S  */
    /********************/

    int16_t gyro_x() { return PS4.gyro_x(); }
    int16_t gyro_y() { return PS4.gyro_y(); }
    int16_t gyro_z() { return PS4.gyro_z(); }
    int16_t accel_x() { return PS4.accel_x(); }
    int16_t accel_y() { return PS4.accel_y(); }
    int16_t accel_z() { return PS4.accel_z(); }

    bool inputsReady;
    void updateInputs();
    void removePairedDevices();
    void batteryWarnCycleProc();
    void attachEvents();

    INPUT_STRUCT inputStruct;

    bool init()
    {
        attachEvents();
        bool output = PS4.begin();
        removePairedDevices();
        return output;
    }

    void attachEvents()
    {
        PS4.attach(updateInputs);
        PS4.attachOnConnect(onConnect);
        PS4.attachOnDisconnect(onDisconnect);
    }

    void removePairedDevices()
    {
        uint8_t pairedDeviceBtAddr[20][6];
        int count = esp_bt_gap_get_bond_device_num();
        esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
        for (int i = 0; i < count; i++)
        {
            esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
        }
    }

    void printDeviceAddress()
    {
        const uint8_t *point = esp_bt_dev_get_address();
        for (int i = 0; i < 6; i++)
        {
            char str[3];
            sprintf(str, "%02x", (int)point[i]);
            Serial.print(str);
            if (i < 5)
            {
                Serial.print(":");
            }
        }
    }

    void onConnect()
    {
        digitalWrite(2, HIGH);
        Serial.println("Connected!");
    }

    void onDisconnect()
    {
        digitalWrite(2, LOW);
        Serial.println("Disconnected!");
    }
    void updateInputs()
    {
        inputsReady = true;
    }
}
