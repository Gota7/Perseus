#pragma once

#include "backend.h"

// Camera definition.
struct ACam
{
    AVec2 offset;
    AVec2 target;
    float rotation;
    float zoom;

    float GetX();
    float GetY();
    void SetX(float v);
    void SetY(float v);
    void MoveX(float v);
    void MoveY(float v);
};

// Scale item.
#include "screen.h"
#define SCALE(x) x * Screen::scale
#define DESCALE(x) x / Screen::scale