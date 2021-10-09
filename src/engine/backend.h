#pragma once

#include "color.h"
#include "input.h"
#include "shaders.h"
#include "vec.h"
#include "medusa/texture.h"
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
void ADrawTexture(ATex tex, float srcX, float srcY, float srcWidth, float srcHeight, float destX, float destY, float destWidth, float destHeight, AVec2 origin = ZERO_VEC, float rotation = 0, AColor tint = COL_WHITE);

// Load a texture.
ATex ALoadTexture(std::string path);

// Unload a texture.
void AUnloadTexture(ATex tex);

// Load a shader.
AShader ALoadShader(std::string vertexFileName, std::string faceFileName);

// Unload a shader.
void AUnloadShader(AShader shader);

// Begin shader mode.
void ABeginShaderMode(AShader shader);

// End shader mode.
void AEndShaderMode();



/*
    Misc. functions.
*/

// Get the current working directory.
std::string AGetWorkingDirectory();

// Get a filename without an extension.
std::string AGetFileNameWithoutExtension(std::string name);