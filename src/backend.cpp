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

void ADrawTexture(void* tex, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, AVec2 origin, float rotation, AColor tint)
{
    DrawTexturePro(*(Texture2D*)tex, { srcX, srcY, srcWidth, srcHeight }, { destX, destY, destWidth, destHeight }, { origin.x, origin.y }, rotation, { tint.r, tint.g, tint.b, tint.a });
}

void* ALoadTexture(std::string path)
{
    void* ret = new Texture2D;
    *(Texture2D*)ret = LoadTexture(path.c_str());
    return ret;
}

void AUnloadTexture(void* tex)
{
    UnloadTexture(*(Texture2D*)tex);
    delete (Texture2D*)tex;
}

void* ALoadShader(std::string vertexFileName, std::string faceFileName)
{
    void* ret = new Shader;
    *(Shader*)ret = LoadShader((vertexFileName.compare("") != 0) ? vertexFileName.c_str() : NULL, (faceFileName.compare("") != 0) ? faceFileName.c_str() : NULL);
    return ret;
}

void AUnloadShader(void* shader)
{
    UnloadShader(*(Shader*)shader);
    delete (Shader*)shader;
}

void ABeginShaderMode(void* shader)
{
    BeginShaderMode(*(Shader*)shader);
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

void AInitAudioDevices()
{
    InitAudioDevice();
}

void ASetAudioDefaultBufferSize(s32 numSamples)
{
    SetAudioStreamBufferSizeDefault(numSamples);
}

void* ALoadAudioStream(u32 sampleRate, u32 sampleSize, u32 channels)
{
    void* ret = new AudioStream;
    *(AudioStream*)ret = LoadAudioStream(sampleRate, sampleSize, channels);
    return ret;
}

void AUnloadAudioStream(void* stream)
{
    UnloadAudioStream(*(AudioStream*)stream);
    delete (AudioStream*)stream;
}

bool AIsAudioStreamProcessed(void* stream)
{
    return IsAudioStreamProcessed(*(AudioStream*)stream);
}

void AUpdateAudioStream(void* stream, const void* data, s32 samplesCount)
{
    UpdateAudioStream(*(AudioStream*)stream, data, samplesCount);
}

void APlayAudioStream(void* stream)
{
    PlayAudioStream(*(AudioStream*)stream);
}

void APauseAudioStream(void* stream)
{
    PauseAudioStream(*(AudioStream*)stream);
}

void AResumeAudioStream(void* stream)
{
    ResumeAudioStream(*(AudioStream*)stream);
}

void AStopAudioStream(void* stream)
{
    StopAudioStream(*(AudioStream*)stream);
}

bool AIsAudioStreamPlaying(void* stream)
{
    return IsAudioStreamPlaying(*(AudioStream*)stream);
}

void ASetAudioStreamVolume(void* stream, f32 volume)
{
    SetAudioStreamVolume(*(AudioStream*)stream, volume);
}

void ASetAudioStreamPitch(void* stream, f32 pitch)
{
    SetAudioStreamPitch(*(AudioStream*)stream, pitch);
}

void ACloseAudioDevices()
{
    CloseAudioDevice();
}