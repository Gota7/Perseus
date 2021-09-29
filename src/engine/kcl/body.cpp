#include "body.h"

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
    if (y < 0 || y >= kclHeight) return KCL_SOLID;
    return kclTiles[y * kclWidth + x];
}

void KclBody::InitBounds(Vector2 offset, Vector2 size)
{
    boundsOffset.x = offset.x + size.x / 4;
    boundsOffset.y = offset.y + size.y / 4;
    bounds.halfSize.x = size.x / 2;
    bounds.halfSize.y = size.y / 2;
}

void KclBody::SetPosition(Vector2 pos)
{
    position.x = pos.x;
    position.y = pos.y;
    bounds.center = { position.x + boundsOffset.x, position.y + boundsOffset.y };
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
    bounds.center = { position.x + boundsOffset.x, position.y + boundsOffset.y };
    //if (position.y < 0) position.y = 0;

}

bool KclBody::CheckGround(float startY, float destY, float tileSize, float& outY)
{
    
    // Get starting and end tiles.
    s32 y1 = Pos2Tile(startY, tileSize);
    s32 y2 = Pos2Tile(destY, tileSize);

    // Check all tiles for potential collision.
    for (s32 y = y1; y <= y2; y++)
    {

        // Special case, not starting from top of tile.
        if (y == y1)
        {

        }

        // Start from top of tile.
        else
        {

        }

    }

    // No collision found, simply return.
    outY = destY;
    return false;

}