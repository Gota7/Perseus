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

    // Alpha.
    static AColor ChangeAlpha(const AColor& color, u8 alpha)
    {
        return AColor(color.r, color.g, color.b, alpha);
    }

    // Alpha.
    static AColor ChangeAlpha(AColor& color, u8 alpha)
    {
        return AColor(color.r, color.g, color.b, alpha);
    }

};

// Colors.
const AColor COL_WHITE = AColor(255, 255, 255);
const AColor COL_YELLOW = AColor(253, 249, 0, 255);