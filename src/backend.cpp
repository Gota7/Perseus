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

float AGetFrameTime()
{
    return GetFrameTime();
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

void ADrawRectangle(float x, float y, float width, float height, AColor color)
{
    Color c;
    c.r = color.r;
    c.g = color.g;
    c.b = color.b;
    c.a = color.a;
    DrawRectangleRec({ x, y, width, height }, c);
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

AShader ALoadShader(std::string vertexFileName, std::string faceFileName)
{
    Shader shader = LoadShader((vertexFileName.compare("") != 0) ? vertexFileName.c_str() : NULL, (faceFileName.compare("") != 0) ? faceFileName.c_str() : NULL);
    AShader ret;
    ret.id = shader.id;
    ret.locs = shader.locs;
    return ret;
}

void AUnloadShader(AShader shader)
{
    Shader s;
    s.id = shader.id;
    s.locs = shader.locs;
    UnloadShader(s);
}

void ABeginShaderMode(AShader shader)
{
    Shader s;
    s.id = shader.id;
    s.locs = shader.locs;
    BeginShaderMode(s);
}

void AEndShaderMode()
{
    EndShaderMode();
}

std::string AGetWorkingDirectory()
{
    return std::string(GetWorkingDirectory());
}

std::string AGetFileNameWithoutExtension(std::string name)
{
    return std::string(GetFileNameWithoutExt(name.c_str()));
}