#pragma once

#include "../types.h"
#include "screenData.h"

// Vector for math and positioning.
struct AVec2
{

    // Data members.
    float x;
    float y;

    // Constructor stuff.
    AVec2();
    AVec2(float v);
    AVec2(float x, float y);
    AVec2(EMU v, s32 degree = 0);
    AVec2(EMU x, EMU y, s32 degree = 0);
    AVec2(AVec2& v);

    // Operator overloading.
    AVec2& operator =(const AVec2& v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }
    inline friend AVec2 operator+(AVec2 a, const AVec2& b);
    inline friend AVec2 operator-(AVec2 a, const AVec2& b);
    inline friend AVec2 operator*(AVec2 a, const float& b);
    inline friend AVec2 operator*(float a, const AVec2& b);
    inline friend float operator*(AVec2 a, const AVec2& b);
    inline friend AVec2& operator +=(AVec2& a, const AVec2& b);
    inline friend AVec2& operator -=(AVec2& a, const AVec2& b);
    inline friend AVec2& operator *=(AVec2& a, const float& b);

    // EMU.
    inline void SetX(EMU v, s32 degree = 0);
    inline void SetY(EMU v, s32 degree = 0);
    inline void Set(EMU x, EMU y, s32 degree = 0);
    inline EMU GetX(s32 degree = 0);
    inline EMU GetY(s32 degree = 0);

    // Math operations.
    inline float Mag();
    inline float Mag2();
    inline AVec2 Normalize();
    inline AVec2 Normal();

};