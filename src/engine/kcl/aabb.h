#include "raylib.h"

//AABB for collision detection.
struct AABB
{
    Vector2 center;
    Vector2 halfSize;

    bool Collides(AABB other);
};