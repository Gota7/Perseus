#include "types.h"
#include <stdio.h>

bool KclTileHitsDownward(u32 type, float startY, float endY, float startX, float endX, float tileSize, float& hitY)
{
    
    // No collision here.
    if (type == KCL_NONE || type == KCL_AIR) { return false; }

    // Generic solid collision.
    else if (type == KCL_SOLID)
    {
        hitY = startY;
        return true; 
    }

    // Solid on top only works if we are starting from the top of the tile and not inside.
    else if (type == KCL_SOLID_ON_TOP)
    {

        // Start at top, act like a solid.
        if (startY == 0)
        {
            hitY = startY;
            return true;
        }

        // Not starting at the top, so act like air.
        else
        {
            return false;
        }

    }

    // For everything else, pretend it's just a solid block.
    hitY = startY;
    return true;

}