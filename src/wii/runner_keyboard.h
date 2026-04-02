#pragma once

#include <stdint.h>
#include <stdbool.h>

// Process Wii controller input (Wiimote, Classic Controller, and USB Keyboard)
void WiiKeyboard_processInput(uint16_t currentButtons, uint16_t prevButtons);

// Map Wii buttons to GML key codes (deprecated, use internal mapping)
int32_t WiiKeyboard_mapButton(uint16_t button);

// Initialize USB keyboard support
void WiiKeyboard_init(void);

// Check if USB keyboard is connected
bool WiiKeyboard_isConnected(void);
