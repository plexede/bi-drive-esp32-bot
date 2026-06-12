# ESP32 PS4 Controller Tank Drive

This project implements a tank drive robot controller using an ESP32 and a PS4 controller via Bluetooth.

Implements and draws from the reusability of the [NJIT-ARPA-2026](https://github.com/Wayne-Valley-Robotics/NJIT-ARPA-BLUE) codebase.
Made partly with AI! (this is a feat as I find it hard to tolerate)

## Setup

1. Ensure you have [PlatformIO](https://platformio.org/) installed.
2. Use the [SixaxisPairTool](https://github.com/user-contributions/SixaxisPairTool) to set the ESP32's Bluetooth MAC address on your PS4 controller so it can connect automatically.
3. Connect your ESP32.
4. Build and upload using the PlatformIO UI in VSCode or by running the following command in your terminal:

   ```bash
   pio run --target upload
   ```

5. The onboard LED (GPIO 2) will turn on when the controller is connected.
