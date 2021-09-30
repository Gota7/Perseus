#include "body.h"
#include <stdio.h>

s32 KclBody::Pos2Tile(float pos, float tileSize)
{
    return (s32)(pos / tileSize);
}

float KclBody::Tile2Pos(s32 tile, float tileSize)
{
    return tile * tileSize;
}

u32 KclBody::GetTileType(s32 x, s32 y)
{
    if (x < 0 || x >= kclWidth) return KCL_SOLID;
    if (y < 0 || y >= kclHeight) return KCL_NONE;
    return kclTiles[y * kclWidth + x] & 0xFFFF;
}

void KclBody::InitBounds(Vector2 offset, Vector2 size)
{
    boundsOffset = offset;
    kclSize = size;
}

void KclBody::SetPosition(Vector2 pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

void KclBody::Update(float dt)
{

    // Backup previous state information.
    prevPosition = position;
    prevVelocity = velocity;
    wasHittingLeft = hittingLeft;
    wasHittingRight = hittingRight;
    wasHittingUp = hittingUp;
    wasHittingDown = hittingDown;

    // Set new acceleration and velocity, reset our force queue.
    acceleration.x = force.x / mass;
    acceleration.y = force.y / mass;
    force.x = 0;
    force.y = 0;
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;

    // Max sure we cap velocity.
    if (velocity.x >= maxVelocity.x)
    {
        velocity.x = maxVelocity.x;
    }
    if (velocity.x <= -maxVelocity.x)
    {
        velocity.x = -maxVelocity.x;
    }
    if (velocity.y >= maxVelocity.y)
    {
        velocity.y = maxVelocity.y;
    }
    if (velocity.y <= -maxVelocity.y)
    {
        velocity.y = -maxVelocity.y;
    }

    // Increment position, and calculate new and past coordinates for collision box.
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    float prevX = prevPosition.x + boundsOffset.x;
    float prevY = prevPosition.y + boundsOffset.y;
    float newX = position.x + boundsOffset.x;
    float newY = position.y + boundsOffset.y;

    // If moving downwards or stationary, we may hit the ground.
    if (velocity.y >= 0)
    {
        float collidesY;
        hittingDown = CheckGround(prevY, newY, newX, 16, collidesY);
        if (hittingDown)
        {
            newY = collidesY;
            position.y = newY - boundsOffset.y;
        }
    }

    // If we are moving upwards, hitting the ground is impossible.
    else
    {
        hittingDown = false;
    }

    // If moving rightwards or stationary, we may hit the wall.
    /*if (velocity.x >= 0)
    {
        float collidesX;
        hittingRight = CheckRight(prevX, newX, newY, 16, collidesX);
        if (hittingRight)
        {
            newX = collidesX;
            position.x = newX - boundsOffset.x;
        }
    }
    else
    {
        hittingRight = false;
    }*/

    // If moving upwards or stationary, we may hit the ceiling.
    if (velocity.y <= 0)
    {
        float collidesY;
        hittingUp = CheckCeiling(prevY, newY, newX, 16, collidesY);
        if (hittingUp)
        {
            newY = collidesY;
            position.y = newY - boundsOffset.y;
        }
    }

    // If we are moving downwards, hitting the ceiling is impossible.
    else
    {
        hittingUp = false;
    }

}

bool KclBody::CheckGround(float startY, float destY, float x, float tileSize, float& outY)
{
    
    // Get starting and end tiles.
    // Notice that we are checking against the ground, so we should move where we check to the bottom of the hitbox.
    startY += kclSize.y;
    destY += kclSize.y;
    s32 y1 = Pos2Tile(startY, tileSize);
    s32 y2 = Pos2Tile(destY, tileSize);
    float minX = x;
    float maxX = x + kclSize.x;
    s32 x1 = Pos2Tile(minX, tileSize);
    s32 x2 = Pos2Tile(maxX, tileSize);

    // Check all tiles for potential collision.
    for (s32 y = y1; y <= y2; y++)
    {

        // We need to get where our hitbox intersects along the tile.
        float yTileStart;
        float yTileEnd;

        // Special case, not starting from top of tile.
        if (y == y1)
        {
            yTileStart = (int)startY % (int)tileSize;
            yTileEnd = tileSize;
        }

        // Special case, not ending at bottom of tile.
        else if (y == y2)
        {
            yTileStart = 0;
            yTileEnd = (int)destY % (int)tileSize;
        }

        // Entire tile.
        else
        {
            yTileStart = 0;
            yTileEnd = tileSize;
        }

        // All intersected X tiles.
        for (s32 x = x1; x <= x2; x++)
        {

            // Get where our hitbox intersects along the tile.
            float xTileStart;
            float xTileEnd;

            // Special case, not starting from left of tile.
            if (x == x1)
            {
                xTileStart = (int)minX % (int)tileSize;
                xTileEnd = tileSize;
            }

            // Special case, not ending at right of tile.
            else if (x == x2)
            {
                xTileStart = 0;
                xTileEnd = (int)maxX % (int)tileSize;
            }

            // Entire tile.
            else
            { 
                xTileStart = 0;
                xTileEnd = tileSize;
            }

            // Finally check if we collide with this tile. If so, we return where.
            float hitY;
            bool collides = KclTileHitsDownward(GetTileType(x, y), yTileStart, yTileEnd, xTileStart, xTileEnd, tileSize, hitY);
            if (collides)
            {
                outY = Tile2Pos(y, tileSize) + hitY - kclSize.y;
                return true;
            }

        }

    }

    // No collision found, simply return.
    outY = destY;
    return false;

}

bool KclBody::CheckCeiling(float startY, float destY, float x, float tileSize, float& outY)
{
    
    // Get starting and end tiles.
    s32 y1 = Pos2Tile(startY, tileSize);
    s32 y2 = Pos2Tile(destY, tileSize);
    float minX = x;
    float maxX = x + kclSize.x;
    s32 x1 = Pos2Tile(minX, tileSize);
    s32 x2 = Pos2Tile(maxX, tileSize);

    // Check all tiles for potential collision.
    for (s32 y = y1; y >= y2; y--)
    {

        // We need to get where our hitbox intersects along the tile.
        float yTileStart;
        float yTileEnd;

        // Special case, not starting from top of tile.
        if (y == y1)
        {
            yTileStart = (int)startY % (int)tileSize;
            yTileEnd = tileSize;
        }

        // Special case, not ending at bottom of tile.
        else if (y == y2)
        {
            yTileStart = 0;
            yTileEnd = (int)destY % (int)tileSize;
        }

        // Entire tile.
        else
        {
            yTileStart = 0;
            yTileEnd = tileSize;
        }

        // All intersected X tiles.
        for (s32 x = x1; x <= x2; x++)
        {

            // Get where our hitbox intersects along the tile.
            float xTileStart;
            float xTileEnd;

            // Special case, not starting from left of tile.
            if (x == x1)
            {
                xTileStart = (int)minX % (int)tileSize;
                xTileEnd = tileSize;
            }

            // Special case, not ending at right of tile.
            else if (x == x2)
            {
                xTileStart = 0;
                xTileEnd = (int)maxX % (int)tileSize;
            }

            // Entire tile.
            else
            { 
                xTileStart = 0;
                xTileEnd = tileSize;
            }

            // Finally check if we collide with this tile. If so, we return where.
            float hitY;
            bool collides = KclTileHitsUpward(GetTileType(x, y), yTileStart, yTileEnd, xTileStart, xTileEnd, tileSize, hitY);
            if (collides)
            {
                outY = Tile2Pos(y, tileSize) + hitY;
                return true;
            }

        }

    }

    // No collision found, simply return.
    outY = destY;
    return false;

}

bool KclBody::CheckRight(float startX, float destX, float y, float tileSize, float& outX)
{
    
    // Get starting and end tiles.
    // Notice that we are checking against the right, so we should move where we check to the right of the hitbox.
    startX += kclSize.x;
    destX += kclSize.x;
    s32 x1 = Pos2Tile(startX, tileSize);
    s32 x2 = Pos2Tile(destX, tileSize);
    float minY = y;
    float maxY = y + kclSize.y - 1; // Prevent getting stuck on ground.
    s32 y1 = Pos2Tile(minY, tileSize);
    s32 y2 = Pos2Tile(maxY, tileSize);

    // All intersected X tiles.
    for (s32 x = x1; x <= x2; x++)
    {

        // Get where our hitbox intersects along the tile.
        float xTileStart;
        float xTileEnd;

        // Special case, not starting from left of tile.
        if (x == x1)
        {
            xTileStart = (int)startX % (int)tileSize;
            xTileEnd = tileSize;
        }

        // Special case, not ending at right of tile.
        else if (x == x2)
        {
            xTileStart = 0;
            xTileEnd = (int)destX % (int)tileSize;
        }

        // Entire tile.
        else
        { 
            xTileStart = 0;
            xTileEnd = tileSize;
        }

        // Check all tiles for potential collision.
        for (s32 y = y1; y <= y2; y++)
        {

            // We need to get where our hitbox intersects along the tile.
            float yTileStart;
            float yTileEnd;

            // Special case, not starting from top of tile.
            if (y == y1)
            {
                yTileStart = (int)minY % (int)tileSize;
                yTileEnd = tileSize;
            }

            // Special case, not ending at bottom of tile.
            else if (y == y2)
            {
                yTileStart = 0;
                yTileEnd = (int)maxY % (int)tileSize;
            }

            // Entire tile.
            else
            {
                yTileStart = 0;
                yTileEnd = tileSize;
            }

            // Finally check if we collide with this tile. If so, we return where.
            float hitX;
            bool collides = KclTileHitsRight(GetTileType(x, y), xTileStart, xTileEnd, yTileStart, yTileEnd, tileSize, hitX);
            if (collides)
            {
                outX = Tile2Pos(x, tileSize) + hitX - kclSize.x;
                return true;
            }

        }

    }

    // No collision found, simply return.
    outX = destX;
    return false;

}