#pragma once

#include "../../types.h"

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
};

// Check if intersecting downwards with a tile. All positions are relative to the tile. Returns if it, and where along the Y axis.
bool KclTileHitsDownward(u32 type, float startY, float endY, float startX, float endX, float tileSize, float& hitY);
bool KclTileHitsUpward(u32 type, float startY, float endY, float startX, float endX, float tileSize, float& hitY);
bool KclTileHitsRight(u32 type, float startX, float endX, float startY, float endY, float tileSize, float& hitX);
bool KclTileHitsLeft(u32 type, float startX, float endX, float startY, float endY, float tileSize, float& hitX);