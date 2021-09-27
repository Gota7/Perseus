#pragma once

#include "raylib.h"
#include "raymath.h"
#include "screenData.h"

enum KclTypes
{
    KCL_NONE,
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

// Kcl response.
struct KclResponse
{
    bool hit;
    Vector2 hitPos;
    bool hurt;
    float dist;
};

// Raycast from start to end, return where the object is allowed to go.
KclResponse RaycastTile(KclTypes type, int tileX, int tileY, Ray ray);