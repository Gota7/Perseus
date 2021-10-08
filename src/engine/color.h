#pragma once

#include "types.h"

// Color definition.
struct AColor
{

    // Data.
    u8 r = 0;
    u8 g = 0;
    u8 b = 0;
    u8 a = 0;

    // Constructor.
    AColor(u8 r, u8 g, u8 b, u8 a = 255)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

};

// White.
const AColor COL_WHITE = AColor(255, 255, 255);