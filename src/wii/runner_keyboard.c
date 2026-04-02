#include "runner_keyboard.h"
#include "../runner.h"
#include <ogc/pad.h>
#include <wiikeyboard/keyboard.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Keyboard input handling for Wii using libwiikeyboard (part of libogc)
// Handles USB Keyboard via libwiikeyboard and GameCube/Wii controllers via PAD

// Wii controller button mappings to GML key codes
typedef struct {
    uint16_t padButton;
    int32_t gmlKey;
} PadMapping;

static PadMapping padMappings[] = {
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

// Classic Controller button mappings (expanded)
static PadMapping classicMappings[] = {
    { PAD_CLASSIC_BUTTON_A, 32 },      // Space
    { PAD_CLASSIC_BUTTON_B, 304 },     // Shift
    { PAD_CLASSIC_BUTTON_X, 90 },      // Z
    { PAD_CLASSIC_BUTTON_Y, 88 },      // X
    { PAD_CLASSIC_BUTTON_PLUS, 13 },   // Enter
    { PAD_CLASSIC_BUTTON_UP, 273 },    // Up arrow
    { PAD_CLASSIC_BUTTON_DOWN, 274 },  // Down arrow
    { PAD_CLASSIC_BUTTON_LEFT, 276 },  // Left arrow
    { PAD_CLASSIC_BUTTON_RIGHT, 275 }, // Right arrow
    { PAD_CLASSIC_BUTTON_ZL, 306 },    // Ctrl
    { PAD_CLASSIC_BUTTON_ZR, 308 },    // Alt
    { PAD_CLASSIC_BUTTON_HOME, 27 },   // Escape
    { PAD_CLASSIC_BUTTON_MINUS, 8 },   // Backspace
    { 0, 0 }
};

// Convert libwiikeyboard scancode to GML key code
static int32_t convertScancodeToGml(char sym) {
    // Direct ASCII characters (printable)
    if (sym >= 32 && sym <= 126) {
        return sym;
    }
    
    // Special keys based on libwiikeyboard scancodes
    switch (sym) {
        case 13:  return 13;   // Enter
        case 27:  return 27;   // Escape
        case 8:   return 8;    // Backspace
        case 9:   return 9;    // Tab
        case 127: return 46;   // Delete
        case 128: return 273;  // Up arrow
        case 129: return 274;  // Down arrow
        case 130: return 276;  // Left arrow
        case 131: return 275;  // Right arrow
        case 132: return 278;  // Insert
        case 133: return 279;  // Home
        case 134: return 280;  // End
        case 135: return 281;  // Page Up
        case 136: return 282;  // Page Down
        case 137: return 112;  // F1
        case 138: return 113;  // F2
        case 139: return 114;  // F3
        case 140: return 115;  // F4
        case 141: return 116;  // F5
        case 142: return 117;  // F6
        case 143: return 118;  // F7
        case 144: return 119;  // F8
        case 145: return 120;  // F9
        case 146: return 121;  // F10
        case 147: return 122;  // F11
        case 148: return 123;  // F12
        case 149: return 304;  // Left Shift
        case 150: return 304;  // Right Shift
        case 151: return 306;  // Left Control
        case 152: return 306;  // Right Control
        case 153: return 308;  // Left Alt
        case 154: return 308;  // Right Alt
        default:  return -1;   // Unknown key
    }
}

void WiiKeyboard_init(void) {
    // Initialize USB keyboard using libwiikeyboard
    KEYBOARD_Init(NULL);
    printf("USB Keyboard initialized via libwiikeyboard\n");
    // GameCube and Wii Remote controllers are initialized in main.c
}

bool WiiKeyboard_isConnected(void) {
    // libwiikeyboard doesn't provide a direct connection check
    // Assume connected if initialized successfully
    return true;
}

static int32_t mapPadButton(uint16_t button, bool isClassic) {
    PadMapping* mappings = isClassic ? classicMappings : padMappings;
    for (int i = 0; mappings[i].padButton != 0; i++) {
        if (button & mappings[i].padButton) {
            return mappings[i].gmlKey;
        }
    }
    return -1;
}

void WiiKeyboard_processInput(uint16_t currentButtons, uint16_t prevButtons) {
    // Process USB keyboard input via libwiikeyboard
    keyboard_event ke;
    s32 res = KEYBOARD_GetEvent(&ke);
    while (res) {
        if (ke.type == KEYBOARD_PRESSED) {
            int32_t gmlKey = convertScancodeToGml(ke.sym);
            if (gmlKey > 0) {
                Runner_keyPressed(gmlKey);
            }
        } else if (ke.type == KEYBOARD_RELEASED) {
            int32_t gmlKey = convertScancodeToGml(ke.sym);
            if (gmlKey > 0) {
                Runner_keyReleased(gmlKey);
            }
        }
        res = KEYBOARD_GetEvent(&ke);
    }
    
    // Detect controller type (Classic Controller or standard Wiimote)
    uint32_t expType = PAD_Expansion(0);
    bool isClassic = (expType == PAD_EXP_CLASSIC);
    
    // Handle button presses for gamepad
    uint16_t pressed = currentButtons & ~prevButtons;
    uint16_t released = ~currentButtons & prevButtons;
    
    for (int i = 0; padMappings[i].padButton != 0; i++) {
        if (pressed & padMappings[i].padButton) {
            Runner_keyPressed(padMappings[i].gmlKey);
        }
        if (released & padMappings[i].padButton) {
            Runner_keyReleased(padMappings[i].gmlKey);
        }
    }
    
    // Handle Classic Controller buttons if connected
    if (isClassic) {
        for (int i = 0; classicMappings[i].padButton != 0; i++) {
            if (pressed & classicMappings[i].padButton) {
                Runner_keyPressed(classicMappings[i].gmlKey);
            }
            if (released & classicMappings[i].padButton) {
                Runner_keyReleased(classicMappings[i].gmlKey);
            }
        }
        
        // Handle Classic Controller analog sticks
        Stick_t stick = PAD_ClassicStick(0);
        
        // Left stick X axis
        if (stick.x < -30) {
            Runner_keyDown(276); // Left
        } else if (stick.x > 30) {
            Runner_keyDown(275); // Right
        }
        
        // Left stick Y axis
        if (stick.y < -30) {
            Runner_keyDown(274); // Down
        } else if (stick.y > 30) {
            Runner_keyDown(273); // Up
        }
        
        // Right stick (optional support)
        Stick_t rightStick = PAD_ClassicRightStick(0);
        if (rightStick.x < -30) {
            Runner_keyDown(276); // Left
        } else if (rightStick.x > 30) {
            Runner_keyDown(275); // Right
        }
        if (rightStick.y < -30) {
            Runner_keyDown(274); // Down
        } else if (rightStick.y > 30) {
            Runner_keyDown(273); // Up
        }
    } else {
        // Handle standard Wiimote analog stick (if available via Nunchuk)
        Stick_t stick = PAD_Stick(0);
        
        // Left stick X axis
        if (stick.x < -30) {
            Runner_keyDown(276); // Left
        } else if (stick.x > 30) {
            Runner_keyDown(275); // Right
        }
        
        // Left stick Y axis
        if (stick.y < -30) {
            Runner_keyDown(274); // Down
        } else if (stick.y > 30) {
            Runner_keyDown(273); // Up
        }
    }
}
