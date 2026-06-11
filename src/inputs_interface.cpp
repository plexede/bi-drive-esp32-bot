#include "inputs_interface.h"
#include <PS4Controller.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

#define DEADZONE 4 // TODO: adjust this!
namespace inputs_interface
{
    int filterDeadzone(int _input, int _deadZone)
    {
        if (_input > _deadZone || _input < -_deadZone)
        {
            return _input;
        }
        return 0;
    }

    bool inputsReady;
    void onConnect();
    void onDisconnect();
    void updateInputs();
    void removePairedDevices();
    void batteryWarnCycleProc();
    void attachEvents();

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