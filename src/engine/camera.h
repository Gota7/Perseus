#pragma once

#include <raylib.h>
#include "screen.h"

// Scale item.
#define SCALE(x) x * Screen::scale
#define DESCALE(x) x / Screen::scale

// Camera position X.
float GetCamPosX(Camera2D* cam);

// Camera position Y.
float GetCamPosY(Camera2D* cam);

// Set the camera position X.
void SetCamPosX(Camera2D* cam, float newPos);

// Set the camera position Y.
void SetCamPosY(Camera2D* cam, float newPos);

// Move the camera position X.
void MoveCamX(Camera2D* cam, float off);

// Move the camera position Y.
void MoveCamY(Camera2D* cam, float off);