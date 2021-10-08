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

void ADrawTexture(ATex tex, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, AVec2 origin, float rotation, AColor tint)
{
    Texture2D ret;
    ret.id = tex.id;
    ret.format = tex.format;
    ret.width = tex.width;
    ret.height = tex.height;
    ret.mipmaps = tex.mipmaps;
    DrawTexturePro(ret, { srcX, srcY, srcWidth, srcHeight }, { destX, destY, destWidth, destHeight }, { origin.x, origin.y }, rotation, { tint.r, tint.g, tint.b, tint.a });
}

ATex ALoadTexture(std::string path)
{
    Texture2D tex = LoadTexture(path.c_str());
    ATex ret;
    ret.id = tex.id;
    ret.format = tex.format;
    ret.width = tex.width;
    ret.height = tex.height;
    ret.mipmaps = tex.mipmaps;
    return ret;
}

void AUnloadTexture(ATex tex)
{
    Texture2D ret;
    ret.id = tex.id;
    ret.format = tex.format;
    ret.width = tex.width;
    ret.height = tex.height;
    ret.mipmaps = tex.mipmaps;
    UnloadTexture(ret);
}

std::string AGetWorkingDirectory()
{
    return std::string(GetWorkingDirectory());
}

std::string AGetFileNameWithoutExtension(std::string name)
{
    return std::string(GetFileNameWithoutExt(name.c_str()));
}