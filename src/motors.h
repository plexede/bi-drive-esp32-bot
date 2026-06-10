#pragma once

/**
 * @brief Stops both motors by setting PWM to 0.
 */
void stopMotors();

/**
 * @brief Drives the motors with specified power levels.
 * 
 * @param left Power level for the left motor (-255 to 255).
 * @param right Power level for the right motor (-255 to 255).
 */
void drive(int left, int right);
