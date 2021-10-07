#pragma once

#include "backend.h"
#include "screenData.h"
#include "scene.h"

// Screen struct.
struct Screen
{

    // Data.
    static int width;
    static int height;
    static float scale;
    static bool fullscreen;

    // Initialize screen.
    static void Init();

    // Set size with width.
    static void SetSizeW(int w);
    
    // Set size with height.
    static void SetSizeH(int h);

    // Toggle fullscreen.
    static void Fullscreen();

    // Save screen settings.
    static void Save();

};