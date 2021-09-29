#include "types.h"

bool KclTileHitsDownward(u32 type, float startY, float endY, float startX, float endX, float tileSize, float& hitY)
{
    if (type == 0) { return false; }
    hitY = endY;
    return true;
}