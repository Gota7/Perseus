#pragma once

#include "color.h"
#include "input.h"
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

// Drawing functions.
void ADrawRectangle(float x, float y, float width, float height, AColor color);