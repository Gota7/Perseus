#include "kcl.h"
#include "stdio.h"

KclResponse RaycastTile(KclTypes type, int tileX, int tileY, Ray ray)
{
    KclResponse k;
    k.hit = false;
    k.hurt = false;
    float originX = (float)tileX * TILE_SIZE;
    float originY = (float)tileY * TILE_SIZE;
    if (type == KCL_SOLID)
    {
        printf("%f %f %f %f %f %f %f\n", originX, originY, originX + TILE_SIZE, originY + TILE_SIZE, ray.position.x, ray.position.y, ray.position.z);
        RayCollision c = GetRayCollisionQuad(ray, { originX, originY + TILE_SIZE, 0 }, { originX, originY, 0 }, { originX + TILE_SIZE, originY, 0 }, { originX + TILE_SIZE, originY + TILE_SIZE, 0 } );
        k.hit = c.hit;
        k.hitPos.x = c.point.x;
        k.hitPos.y = c.point.y;
        k.dist = c.distance;
        if (k.hit)
        {
            printf("Hi!\n");
        }
    }
    return k;
}