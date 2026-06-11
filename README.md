# ESP32 PS4 Controller Tank Drive

This project implements a tank drive robot controller using an ESP32 and a PS4 controller via Bluetooth.

Implements and draws from the reusability of the [NJIT-ARPA-2026](https://github.com/Wayne-Valley-Robotics/NJIT-ARPA-BLUE) codebase.
Made partly with AI! (this is a feat as I find it hard to tolerate)

## Features
- Bluetooth connectivity using `PS4_Controller_Host`.
- Tank drive logic with deadzone filtering.
- Motor control abstraction.

## Setup
1. Ensure you have [PlatformIO](https://platformio.org/) installed.
2. Use the [SixaxisPairTool](https://github.com/user-contributions/SixaxisPairTool) to set the ESP32's Bluetooth MAC address on your PS4 controller so it can pair automatically.
3. The `PS4_Controller_Host` library handles the connection; ensure your ESP32 is powered and ready to pair when the controller is put into pairing mode.
2. Connect your ESP32.
3. Build and upload using:
   ```bash
   pio run --target upload
   ```
4. The onboard LED (GPIO 2) will turn on when the controller is connected.
