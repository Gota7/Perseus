#pragma once

#include "types.h"
#include "../types.h"
#include "../vec.h"

// Collision path.
struct CollisionPath
{

    // For direction moving.
    s32 startTilePath;
    s32 endTilePath;
    float startTilePathRem;
    float endTilePathRem;

    // For "walls" around direction moving.
    s32 startTileAround;
    s32 endTileAround;
    float startTileAroundRem;
    float endTileAroundRem;

};

// KCL body.
struct KclBody
{

    // Generic stuff.
    AVec2 position = AVec2(0.0f);
    AVec2 velocity = AVec2(0.0f);
    AVec2 acceleration = AVec2(0.0f);
    AVec2 force = AVec2(0.0f);
    AVec2 maxVelocity = AVec2(100.0f);
    float mass = 1;
    AVec2 prevPosition = AVec2(0.0f);
    AVec2 prevVelocity = AVec2(0.0f);
    
    // Bounding box.
    AVec2 kclSize;
    AVec2 boundsOffset = AVec2(0.0f);

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
    void InitBounds(AVec2 offset, AVec2 size);
    void SetPosition(AVec2 pos);
    void Update(float dt);

    // Private physics functions.
private:
    void ApplyXInertia(float inertia);
    void ApplyYInertia(float inertia);
    
    /*bool CheckGround(float startY, float destY, float x, float tileSize, float& outY);
    bool CheckCeiling(float startY, float destY, float x, float tileSize, float& outY);
    bool CheckRight(float startX, float destX, float y, float tileSize, float& outX);
    bool CheckLeft(float startX, float destX, float y, float tileSize, float& outX);*/

};