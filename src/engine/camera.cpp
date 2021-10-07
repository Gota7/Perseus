#include "camera.h"

float ACam::GetX()
{
    return DESCALE(offset.x);
}

float ACam::GetY()
{
    return DESCALE(offset.y);
}

void ACam::SetX(float newPos)
{
    offset.x = SCALE(newPos);
}

void ACam::SetY(float newPos)
{
    offset.y = SCALE(newPos);
}

void ACam::MoveX(float off)
{
    offset.x += SCALE(off);
}

void ACam::MoveY(float off)
{
    offset.y += SCALE(off);
}