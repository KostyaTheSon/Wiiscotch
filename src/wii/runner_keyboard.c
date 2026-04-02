#include "runner_keyboard.h"
#include "../runner.h"
#include <ogc/pad.h>
#include <wiiuse/wpad.h>
#include <wiikeyboard/keyboard.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Keyboard input handling for Wii using libwiikeyboard (part of libogc)
// Handles USB Keyboard via libwiikeyboard and GameCube controller via PAD

extern Runner* g_runner;  // Global runner instance for accessing keyboard state

// Convert ASCII character to GML key code
static int32_t convertCharToGml(char c) {
    // Direct ASCII characters (printable)
    if (c >= 32 && c <= 126) {
        return c;
    }
    
    // Special characters
    switch (c) {
        case 8:   return 8;    // Backspace
        case 9:   return 9;    // Tab
        case 13:  return 13;   // Enter
        case 27:  return 27;   // Escape
        default:  return -1;   // Unknown
    }
}

void WiiKeyboard_init(void) {
    // Initialize USB keyboard using libwiikeyboard with no callback
    // We'll use getchar() approach instead
    KEYBOARD_Init(NULL);
    printf("USB Keyboard initialized via libwiikeyboard\n");
    // GameCube controller is initialized in main.c
}

bool WiiKeyboard_isConnected(void) {
    // libwiikeyboard doesn't provide a direct connection check
    // Assume connected if initialized successfully
    return true;
}

void WiiKeyboard_processInput(uint16_t currentButtons, uint16_t prevButtons) {
    RunnerKeyboardState* kb = g_runner->keyboard;
    
    // Process USB keyboard input via libwiikeyboard using getchar()
    // Check if there's a character available without blocking
    char c;
    ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
    while (bytesRead > 0) {
        int32_t gmlKey = convertCharToGml(c);
        if (gmlKey > 0) {
            RunnerKeyboard_onKeyDown(kb, gmlKey);
            RunnerKeyboard_onKeyUp(kb, gmlKey);  // Immediate release for character input
        }
        bytesRead = read(STDIN_FILENO, &c, 1);
    }
    
    // Handle button presses for GameCube controller
    uint16_t pressed = currentButtons & ~prevButtons;
    uint16_t released = ~currentButtons & prevButtons;
    
    // Standard GameCube button mappings
    static const struct { uint16_t button; int32_t gmlKey; } padMappings[] = {
        { PAD_BUTTON_A, 32 },      // Space
        { PAD_BUTTON_B, 304 },     // Shift
        { PAD_BUTTON_X, 90 },      // Z
        { PAD_BUTTON_Y, 88 },      // X
        { PAD_BUTTON_START, 13 },  // Enter
        { PAD_BUTTON_UP, 273 },    // Up arrow
        { PAD_BUTTON_DOWN, 274 },  // Down arrow
        { PAD_BUTTON_LEFT, 276 },  // Left arrow
        { PAD_BUTTON_RIGHT, 275 }, // Right arrow
        { PAD_TRIGGER_L, 306 },    // Ctrl
        { PAD_TRIGGER_R, 308 },    // Alt
        { 0, 0 }
    };
    
    for (int i = 0; padMappings[i].button != 0; i++) {
        if (pressed & padMappings[i].button) {
            RunnerKeyboard_onKeyDown(kb, padMappings[i].gmlKey);
        }
        if (released & padMappings[i].button) {
            RunnerKeyboard_onKeyUp(kb, padMappings[i].gmlKey);
        }
    }
}
