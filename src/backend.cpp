#include "raylib.h"
#include "engine/backend.h"
#include <map>

// Implement raylib functions.
void AInitWindow(s32 width, s32 height, std::string title)
{
    InitWindow(width, height, title.c_str());
}

void ASetWindowSize(s32 width, s32 height)
{
    SetWindowSize(width, height);
}

void ASetFPS(s32 FPS)
{
    SetTargetFPS(FPS);
}

s32 AGetMonitorWidth(s32 monitor)
{
    return GetMonitorWidth(monitor);
}

s32 AGetMonitorHeight(s32 monitor)
{
    return GetMonitorHeight(monitor);
}

std::map<AInputButton, KeyboardKey> keysMap = 
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

bool AButtonDown(AInputButton button)
{
    return IsKeyDown(keysMap[button]);
}

bool AButtonUp(AInputButton button)
{
    return IsKeyUp(keysMap[button]);
}

bool AButtonPressed(AInputButton button)
{
    return IsKeyPressed(keysMap[button]);
}

bool AButtonReleased(AInputButton button)
{
    return IsKeyReleased(keysMap[button]);
}