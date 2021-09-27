#pragma once

#include "raylib.h"
#include <map>

// Actual buttons.
enum InputButtons
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_ATTACK,
    BUTTON_JUMP,
    BUTTON_START,
    BUTTON_SELECT
};

// Input.
struct Input
{

    // Keys map.
    static std::map<InputButtons, KeyboardKey> keysMap;

    // Button down.
    static bool Down(InputButtons button);

    // Button up.
    static bool Up(InputButtons button);
    
    // Button pressed.
    static bool Pressed(InputButtons button);

    // Button released.
    static bool Released(InputButtons button);

};