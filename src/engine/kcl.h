#pragma once

#include "raylib.h"
#include "raymath.h"
#include "screenData.h"

#include "kcl/aabb.h"
#include "kcl/body.h"
#include "kcl/types.h"

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