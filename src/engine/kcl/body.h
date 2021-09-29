#pragma once

#include "raylib.h"
#include "aabb.h"
#include "types.h"
#include "../../types.h"

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
    u32* kclTiles = nullptr;
    u32 kclWidth = 0;
    u32 kclHeight = 0;
    s32 Pos2Tile(float pos, float tileSize);
    float Tile2Pos(s32 tile, float tileSize);
    u32 GetTileType(s32 x, s32 y);

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
    void InitBounds(Vector2 offset, Vector2 size);
    void SetPosition(Vector2 pos);
    void Update(float dt);

    // Private physics functions.
private:
    bool CheckGround(float startY, float destY, float tileSize, float& outY);

};