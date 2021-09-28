#pragma once

#include "raylib.h"
#include "aabb.h"

// KCL body.
struct KclBody
{

    // Generic stuff.
    Vector2 position = { 0, 0 };
    Vector2 velocity = { 0, 0 };
    Vector2 acceleration = { 0, 0 };
    Vector2 force = { 0, 0 };
    Vector2 maxVelocity = { 100, 100 };
    float mass = 1;
    Vector2 prevPosition = { 0, 0 };
    Vector2 prevVelocity = { 0, 0 };
    
    // Bounding box.
    KclAABB bounds;
    Vector2 boundsOffset = { 0, 0 };

    // Kcl map information.

    // Results.
    bool wasHittingLeft = false;
    bool hittingLeft = false;
    bool wasHittingRight = false;
    bool hittingRight = false;
    bool wasHittingUp = false;
    bool hittingUp = false;
    bool wasHittingDown = false;
    bool hittingDown = false;

    // Settings.
    bool isCollideable = false;
    bool isSolid = false;

    // Physics functions.
    void Update(float dt);

};