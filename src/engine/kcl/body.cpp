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
    return kclTiles[y * kclWidth + x];
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

    // Backups.
    prevPosition = position;
    prevVelocity = velocity;
    wasHittingLeft = hittingLeft;
    wasHittingRight = hittingRight;
    wasHittingUp = hittingUp;
    wasHittingDown = hittingDown;

    // Physics update.
    acceleration.x = force.x / mass;
    acceleration.y = force.y / mass;
    force.x = 0;
    force.y = 0;
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
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

    // TEMP.
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    float prevX = prevPosition.x + boundsOffset.x;
    float prevY = prevPosition.y + boundsOffset.y;
    float newX = position.x + boundsOffset.x;
    float newY = position.y + boundsOffset.y;
    if (velocity.y >= 0)
    {
        float collidesY;
        hittingDown = CheckGround(prevY, newY, prevX, 16, collidesY);
        printf("%f %f %f\n", prevPosition.y, position.y, collidesY);
        if (hittingDown)
        {
            newY = collidesY;
            position.y = newY - boundsOffset.y;
        }
    }

}

bool KclBody::CheckGround(float startY, float destY, float x, float tileSize, float& outY)
{
    
    // Get starting and end tiles.
    startY += kclSize.y;
    destY += kclSize.y;
    s32 y1 = Pos2Tile(startY, tileSize);
    s32 y2 = Pos2Tile(destY, tileSize);
    float minX = x;
    float maxX = x + kclSize.x;
    s32 x1 = Pos2Tile(minX, tileSize);
    s32 x2 = Pos2Tile(maxX, tileSize);

    // All intersected X tiles.
    for (s32 x = x1; x < x2; x++)
    {

        // Bounds.
        float xTileStart;
        float xTileEnd;

        // Special case, not starting from top of tile.
        if (x == x1)
        {
            xTileStart = (int)minX % (int)tileSize;
            xTileEnd = tileSize;
        }

        // Special case, not ending at bottom of tile.
        else if(x == x2 - 1)
        {
            xTileStart = 0;
            xTileEnd = tileSize;
        }

        // Entire tile.
        else
        {
            xTileStart = 0;
            xTileEnd = (int)maxX % (int)tileSize;
        }

        // Check all tiles for potential collision.
        for (s32 y = y1; y <= y2; y++)
        {

            // Bounds.
            float yTileStart;
            float yTileEnd;

            // Special case, not starting from top of tile.
            if (y == y1)
            {
                yTileStart = (int)startY % (int)tileSize;
                yTileEnd = tileSize;
            }

            // Special case, not ending at bottom of tile.
            else if(y == y2 - 1)
            {
                yTileStart = 0;
                yTileEnd = tileSize;
            }

            // Entire tile.
            else
            {
                yTileStart = 0;
                yTileEnd = (int)destY % (int)tileSize;
            }

            // Collision.
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