#include "input.h"

std::map<InputButtons, KeyboardKey> Input::keysMap = 
{
    { BUTTON_LEFT, KEY_LEFT },
    { BUTTON_RIGHT, KEY_RIGHT },
    { BUTTON_UP, KEY_UP },
    { BUTTON_DOWN, KEY_DOWN },
    { BUTTON_ATTACK, KEY_X },
    { BUTTON_JUMP, KEY_Z },
    { BUTTON_START, KEY_ENTER },
    { BUTTON_SELECT, KEY_RIGHT_SHIFT }
};

bool Input::Down(InputButtons button)
{
    return IsKeyDown(keysMap[button]);
}

bool Input::Up(InputButtons button)
{
    return IsKeyUp(keysMap[button]);
}

bool Input::Pressed(InputButtons button)
{
    return IsKeyPressed(keysMap[button]);
}

bool Input::Released(InputButtons button)
{
    return IsKeyReleased(keysMap[button]);
}