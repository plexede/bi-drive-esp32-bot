# ESP32 PS4 Controller Tank Drive

This project implements a tank drive robot controller using an ESP32 and a PS4 controller via Bluetooth.

## Features
- Bluetooth connectivity using `PS4_Controller_Host`.
- Tank drive logic with deadzone filtering.
- Motor control abstraction.

## Setup
1. Ensure you have [PlatformIO](https://platformio.org/) installed.
2. Connect your ESP32.
3. Build and upload using:
   ```bash
   pio run --target upload
   ```
4. The onboard LED (GPIO 2) will turn on when the controller is connected.
