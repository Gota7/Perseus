#pragma once

#include "raylib.h"

//AABB for collision detection.
struct KclAABB
{
    Vector2 center = { 0, 0 };
    Vector2 halfSize = { 0, 0 };

    bool Collides(KclAABB other);
};