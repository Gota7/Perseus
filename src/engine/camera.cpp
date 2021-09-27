#include "camera.h"

float GetCamPosX(Camera2D* cam)
{
    return DESCALE(cam->offset.x);
}

float GetCamPosY(Camera2D* cam)
{
    return DESCALE(cam->offset.y);
}

void SetCamPosX(Camera2D* cam, float newPos)
{
    cam->offset.x = SCALE(newPos);
}

void SetCamPosY(Camera2D* cam, float newPos)
{
    cam->offset.y = SCALE(newPos);
}

void MoveCamX(Camera2D* cam, float off)
{
    cam->offset.x += SCALE(off);
}

void MoveCamY(Camera2D* cam, float off)
{
    cam->offset.y += SCALE(off);
}