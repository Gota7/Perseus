#pragma once

#include "color.h"
#include "input.h"
#include "shaders.h"
#include "vec.h"
#include <string>

/*

    Declares all the functions that must be implemented for the Athens Engine to work.

*/



/*
    Window functions.
*/

// Initialize the window and set its width, height, and title.
void AInitWindow(s32 width, s32 height, std::string title);

// Set the size of the window.
void ASetWindowSize(s32 width, s32 height);

// Set how many frames per second the game is.
void ASetFPS(s32 FPS);

// Get the time of the last frame.
float AGetFrameTime();

// Get the monitor width given the monitor ID.
s32 AGetMonitorWidth(s32 monitor);

// Get the monitor height given the monitor ID.
s32 AGetMonitorHeight(s32 monitor);



/*
    Input functions.
*/

// Check if a button is down.
bool AButtonDown(AInputButton button);

// Check if a button is up.
bool AButtonUp(AInputButton button);

// Check if a button was pressed just this frame.
bool AButtonPressed(AInputButton button);

// Check if a button was released just this frame.
bool AButtonReleased(AInputButton button);



/*
    Graphics functions.
*/

// Draw a rectangle.
void ADrawRectangle(float x, float y, float width, float height, AColor color = COL_WHITE);

// Draw a texture.
void ADrawTexture(void* tex, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, AVec2 origin = ZERO_VEC, float rotation = 0, AColor tint = COL_WHITE);

// Load a texture.
void* ALoadTexture(std::string path);

// Unload a texture.
void AUnloadTexture(void* tex);

// Load a shader.
void* ALoadShader(std::string vertexFileName, std::string faceFileName);

// Unload a shader.
void AUnloadShader(void* shader);

// Begin shader mode.
void ABeginShaderMode(void* shader);

// End shader mode.
void AEndShaderMode();



/*
    Audio functions.
*/

// Initialize audio devices.
void AInitAudioDevices();

// Set default buffer size.
void ASetAudioDefaultBufferSize(u32 numSamples);

// Load an audio stream.
void* ALoadAudioStream(u32 sampleRate, u32 sampleSize, u32 channels);

// Unload an audio stream.
void AUnloadAudioStream(void* stream);

// If an audio stream has played through all its samples.
bool AIsAudioStreamProcessed(void* stream);

// Update an audio stream with more data to play.
void AUpdateAudioStream(void* stream, const void* data, s32 samplesCount);

// Play an audio stream.
void APlayAudioStream(void* stream);

// Pause an audio stream.
void APauseAudioStream(void* stream);

// Resume an audio stream.
void AResumeAudioStream(void* stream);

// Stop an audio stream.
void AStopAudioStream(void* stream);

// If an audio stream is playing.
bool AIsAudioStreamPlaying(void* stream);

// Set the volume of an audio stream.
void ASetAudioStreamVolume(void* stream, f32 volume);

// Set the pitch of an audio stream.
void ASetAudioStreamPitch(void* stream, f32 pitch);

// Close audio devices.
void ACloseAudioDevices();



/*
    Misc. functions.
*/

// Get the current working directory.
std::string AGetWorkingDirectory();

// Get a filename without an extension.
std::string AGetFileNameWithoutExtension(std::string name);