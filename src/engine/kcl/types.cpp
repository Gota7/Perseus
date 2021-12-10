#include "types.h"
#include <stdio.h>

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

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

    // Left slab.
    else if (type == KCL_SOLID_SLAB_LEFT)
    {

        // If starts to right, can't intersect.
        if (startX >= tileSize / 2 - 1)
        {
            return false;
        }
        else
        {
            hitY = startY;
            return true;
        }

    }

    // Right slab.
    else if (type == KCL_SOLID_SLAB_RIGHT)
    {

        // If end to right, can't intersect.
        if (endX <= tileSize / 2)
        {
            return false;
        }
        else
        {
            hitY = startY;
            return true;
        }

    }

    // Top slab.
    else if (type == KCL_SOLID_SLAB_TOP)
    {

        // If past top.
        if (startY >= tileSize / 2)
        {
            return false;
        }

        // Intersecting with top.
        else
        {
            hitY = startY;
            return true;
        }

    }

    // Bottom slab.
    else if (type == KCL_SOLID_SLAB_BOTTOM)
    {

        // If going through bottom.
        if (endY >= tileSize / 2)
        {
            hitY = tileSize / 2;
            return true;
        }

        // Top is clear.
        else
        {
            return false;
        }

    }

    // Pass-through.
    else if (type == KCL_SOLID_ON_BOTTOM || type == KCL_SOLID_ON_LEFT || type == KCL_SOLID_ON_RIGHT) { return false; }

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

    // Top-right space slopes.
    else if (type == KCL_SLOPE_TOP_RIGHT_SPACE)
    {
        if (startX <= 0) { hitY = 0; }
        else if (startX > tileSize) { hitY = MIN(tileSize, endY); }
        else { hitY = MIN(startX, endY); }
        return true;
    }

    // Top-left space slopes.
    else if (type == KCL_SLOPE_TOP_LEFT_SPACE)
    {
        if (endX <= 0) { hitY = MIN(tileSize, endY); }
        else if (endX > tileSize) { hitY = 0; }
        else { hitY = MIN(tileSize - endX, endY); }
        return true;
    }

    // TODO:
    else if (type == KCL_LADDER || type == KCL_LADDER_LEFT || type == KCL_LADDER_RIGHT) { return false; }

    // For everything else, pretend it's just a solid block.
    hitY = startY;
    return true;

}

bool KclTileHitsUpward(u32 type, float startY, float endY, float startX, float endX, float tileSize, float& hitY)
{
    
    // No collision here.
    if (type == KCL_NONE || type == KCL_AIR) { return false; }

    // Generic solid collision.
    else if (type == KCL_SOLID)
    {
        hitY = endY;
        return true; 
    }

    // Left slab.
    else if (type == KCL_SOLID_SLAB_LEFT)
    {

        // If starts to right, can't intersect.
        if (startX >= tileSize / 2 - 1)
        {
            return false;
        }
        else
        {
            hitY = endY;
            return true;
        }

    }

    // Right slab.
    else if (type == KCL_SOLID_SLAB_RIGHT)
    {

        // If end to right, can't intersect.
        if (endX <= tileSize / 2)
        {
            return false;
        }
        else
        {
            hitY = endY;
            return true;
        }

    }

    // Pass-through.
    else if (type == KCL_SOLID_ON_TOP || type == KCL_SOLID_ON_LEFT || type == KCL_SOLID_ON_RIGHT) { return false; }

    // Solid on bottom only works if we are starting from the bottom of the tile and not inside.
    else if (type == KCL_SOLID_ON_TOP)
    {

        // Start at bottom, act like a solid.
        if (endY == tileSize)
        {
            hitY = tileSize;
            return true;
        }

        // Not starting at the bottom, so act like air.
        else
        {
            return false;
        }

    }

    // TODO:
    else if (type == KCL_LADDER || type == KCL_LADDER_LEFT || type == KCL_LADDER_RIGHT) { return false; }

    // For everything else, pretend it's just a solid block.
    hitY = endY;
    return true;

}

bool KclTileHitsRight(u32 type, float startX, float endX, float startY, float endY, float tileSize, float& hitX)
{

    // No collision here.
    if (type == KCL_NONE || type == KCL_AIR) { return false; }

    // Generic solid collision.
    else if (type == KCL_SOLID)
    {
        hitX = startX;
        return true; 
    }

    // Pass-through.
    else if (type == KCL_SOLID_ON_TOP || type == KCL_SOLID_ON_LEFT || type == KCL_SOLID_ON_BOTTOM) { return false; }

    // Top-right space slopes.
    else if (type == KCL_SLOPE_TOP_RIGHT_SPACE)
    {
        if (startX <= 0)
        {
            hitX = startX;
            return true;
        }
        else if (startX > endY)
        {
            return false;
        }
        else
        {
            hitX = endY;
            return true;
        }
    }

    // TODO:
    else if (type == KCL_LADDER || type == KCL_LADDER_LEFT || type == KCL_LADDER_RIGHT) { return false; }

    // For everything else, pretend it's just a solid block.
    hitX = startX;
    return true;

}

bool KclTileHitsLeft(u32 type, float startX, float endX, float startY, float endY, float tileSize, float& hitX)
{

    // No collision here.
    if (type == KCL_NONE || type == KCL_AIR) { return false; }

    // Generic solid collision.
    else if (type == KCL_SOLID)
    {
        hitX = endX;
        return true; 
    }

    // Pass-through.
    else if (type == KCL_SOLID_ON_TOP || type == KCL_SOLID_ON_LEFT || type == KCL_SOLID_ON_BOTTOM) { return false; }

    // TODO:
    else if (type == KCL_LADDER || type == KCL_LADDER_LEFT || type == KCL_LADDER_RIGHT) { return false; }

    // For everything else, pretend it's just a solid block.
    hitX = endX;
    return true;

}

/*
enum KclTypes
{
    KCL_NONE,
    KCL_AIR,
    KCL_SOLID,
    KCL_SOLID_ON_TOP,
    KCL_SOLID_ON_BOTTOM,
    KCL_SOLID_SLAB_TOP,
    KCL_SOLID_SLAB_BOTTOM,
    KCL_SOLID_SLAB_LEFT,
    KCL_SOLID_SLAB_RIGHT,
    KCL_LADDER,
    KCL_LADDER_LEFT,
    KCL_LADDER_RIGHT,
    KCL_SOLID_ON_RIGHT,
    KCL_SPIKES_TOP_BOTTOM,
    KCL_SPIKES_LEFT_RIGHT,
    KCL_SPIKES,
    KCL_SOLID_ON_LEFT,
    KCL_SLOPE_TOP_RIGHT_SPACE,
    KCL_SLOPE_TOP_LEFT_SPACE,
    KCL_SLOPE_BOTTOM_RIGHT_SPACE,
    KCL_SLOPE_BOTTOM_LEFT_SPACE,
    KCL_SPIKES_TOP,
    KCL_SPIKES_BOTTOM,
    KCL_SPIKES_LEFT,
    KCL_SPIKES_RIGHT
};*/

void CalcOffsForMovingLeft(u32 type, float x, float y, float tileSize, float& offX, float& offY)
{
    if (type == KCL_SOLID)
    {
        offX = 0;
        offY = 0;
    }
    else 
    {
        offX = 1;
        offY = 0;
    }
}

void CalcOffsForMovingUp(u32 type, float x, float y, float tileSize, float& offX, float& offY)
{
    if (type == KCL_SOLID)
    {
        offX = 0;
        offY = 0;
    }
    else 
    {
        offX = 0;
        offY = 1;
    }
}

bool KclTileCollides(u32 type, float startX, float endX, float startY, float endY, bool dirFlip)
{

    // Obviously no collision for air.
    if (type == KCL_NONE || type == KCL_AIR) return false;

    // Some general solids.
    if (type == KCL_SOLID || type == KCL_LADDER || type == KCL_LADDER_LEFT || type == KCL_LADDER_RIGHT
        || type == KCL_SPIKES_TOP_BOTTOM || type == KCL_SPIKES_LEFT_RIGHT || type == KCL_SPIKES
        || type == KCL_SPIKES_TOP || type == KCL_SPIKES_BOTTOM || type == KCL_SPIKES_LEFT || type == KCL_SPIKES_RIGHT)
        return true;

    // So for solid in direction Z, it's important we start at the place we are counting.
    // Intersection is still counted even if we don't do anything in the resolution code.
    if (type == KCL_SOLID_ON_TOP && startY == 0 && !dirFlip) return true;
    if (type == KCL_SOLID_ON_BOTTOM && startY == 1 && dirFlip) return true;
    if (type == KCL_SOLID_ON_LEFT && startX == 0 && !dirFlip) return true;
    if (type == KCL_SOLID_ON_RIGHT && startX == 1 && dirFlip) return true;

    // Solid slabs, only valid for certain halves.
    if (type == KCL_SOLID_SLAB_TOP && ((!dirFlip && startY < 0.5) || (dirFlip && endY < 0.5))) return true;
    if (type == KCL_SOLID_SLAB_BOTTOM && ((!dirFlip && endY >= 0.5) || (dirFlip && startY >= 0.5))) return true;
    if (type == KCL_SOLID_SLAB_LEFT && ((!dirFlip && startX < 0.5) || (dirFlip && endX < 0.5))) return true;
    if (type == KCL_SOLID_SLAB_RIGHT && ((!dirFlip && endX >= 0.5) || (dirFlip && startX >= 0.5))) return true;

    // Rest are not solid.
    return false;

}