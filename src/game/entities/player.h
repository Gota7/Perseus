#pragma once

#include "../../engine.h"

// Physics.
const EMU PLAYER_MOVE_SPEED = 0x5000;
const EMU PLAYER_MOVE_ACCEL = 0xF000;
const EMU PLAYER_MOVE_DEACCEL = 0x20000;
const EMU PLAYER_GRAVITY = 0x40000;
const EMU PLAYER_GRAVITY_JUMP = 0x20000;
const EMU PLAYER_MAX_FALL = 0x30000;
const EMU PLAYER_JUMP = -0x10000;
const EMU PLAYER_ACCEL_AIR = 0x7000;
const EMU PLAYER_DEACCEL_AIR = 0x30000;
const float FLOOR = TILE_SIZE * 9;

// Forward declare.
struct Entity;

// Initialize states.
void PlayerInitStates(u32 behaviorId);
void PlayerInitKCL(Entity* ent);

// Idle state.
void PlayerIdleInit(Entity* ent);
void PlayerIdleMain(Entity* ent);
void PlayerMoveInit(Entity* ent);
void PlayerMoveMain(Entity* ent);
void PlayerFallInit(Entity* ent);
void PlayerFallMain(Entity* ent);
void PlayerFallCleanup(Entity* ent);