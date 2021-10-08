#pragma once

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

typedef int EMU;
const u16 EMU_PER_BLOCK = 0x1000;

struct s24
{
    s32 val : 24;
};

struct u24
{
    u32 val : 24;
};