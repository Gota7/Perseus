#include "vec.h"
#include <tgmath.h>

AVec2::AVec2()
{
    x = 0;
    y = 0;
}

AVec2::AVec2(float v)
{
    x = v;
    y = v;
}

AVec2::AVec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

AVec2::AVec2(EMU v, s32 degree)
{
    Set(v, v, degree);
}

AVec2::AVec2(EMU x, EMU y, s32 degree)
{
    SetX(x, degree);
    SetY(y, degree);
}

AVec2::AVec2(AVec2& v)
{
    x = v.x;
    y = v.y;
}

/*AVec2& AVec2::operator=(AVec2 v)
{
  this->x = v.x;
  this->y = v.y;
  return *this;
}*/

AVec2 operator+(AVec2 a, const AVec2& b)
{
    AVec2 ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

AVec2 operator-(AVec2 a, const AVec2& b)
{
    AVec2 ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

AVec2 operator*(AVec2 a, const float& b)
{
    AVec2 ret;
    ret.x = a.x * b;
    ret.y = a.y * b;
    return ret;
}

AVec2 operator*(float a, const AVec2& b)
{
    AVec2 ret;
    ret.x = b.x * a;
    ret.y = b.y * a;
    return ret;
}

float operator*(AVec2 a, const AVec2& b)
{
    return a.x * b.x + a.y * b.y;
}

AVec2& operator +=(AVec2& a, const AVec2& b)
{
    a = a + b;
    return a;
}

AVec2& operator -=(AVec2& a, const AVec2& b)
{
    a = a - b;
    return a;
}

AVec2& operator *=(AVec2& a, const float& b)
{
    a = a * b;
    return a;
}

void AVec2::SetX(EMU v, s32 degree)
{
    x = EMU_TO_FLOAT(v) * pow(FPS, degree);
}

void AVec2::SetY(EMU v, s32 degree)
{
    y = EMU_TO_FLOAT(v) * pow(FPS, degree);
}

void AVec2::Set(EMU x, EMU y, s32 degree)
{
    SetX(x);
    SetY(y);
}

EMU AVec2::GetX(s32 degree)
{
    return FLOAT_TO_EMU(x / pow(FPS, degree));
}

EMU AVec2::GetY(s32 degree)
{
    return FLOAT_TO_EMU(y / pow(FPS, degree));
}

float AVec2::Mag()
{
    return sqrt(Mag2());
}

float AVec2::Mag2()
{
    return x * x + y * y;
}

AVec2 AVec2::Normalize()
{
    float mag = Mag();
    return AVec2(x / mag, y / mag);
}

AVec2 AVec2::Normal()
{
    return AVec2(x, -y);
}