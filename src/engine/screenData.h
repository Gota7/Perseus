#pragma once

#include "../types.h"

const u8 TILE_SIZE = 16;
const u8 SCREEN_WIDTH_TILES = 27;
const u8 SCREEN_HEIGHT_TILES = 15;
const u16 SCREEN_WIDTH = SCREEN_WIDTH_TILES * TILE_SIZE;
const u16 SCREEN_HEIGHT = SCREEN_HEIGHT_TILES * TILE_SIZE;
const u8 DEFAULT_SCREEN_SCALE = 3;
const u8 FPS = 60;
const u8 DEBUG_MODE = true;
const u8 DEBUG_KCL = true;

#define EMU_TO_FLOAT(x) x * (float)TILE_SIZE / EMU_PER_BLOCK
#define FLOAT_TO_EMU(x) (EMU)((float)x * EMU_PER_BLOCK / TILE_SIZE)