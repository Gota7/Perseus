#pragma once

#include "asset.h"
#include <map>
#include <string>
#include <vector>

// Tiling mode.
enum TileMode
{
    TILE_MODE_SEQUENTIAL,
    TILE_MODE_RANDOM
};

// Place position.
enum PlacePosition
{
    PLACE_POS_TOP_LEFT,
    PLACE_POS_TOP,
    PLACE_POS_TOP_RIGHT,
    PLACE_POS_LEFT,
    PLACE_POS_MIDDLE,
    PLACE_POS_RIGHT,
    PLACE_POS_BOTTOM_LEFT,
    PLACE_POS_BOTTOM,
    PLACE_POS_BOTTOM_RIGHT
};

// Repeating mode.
enum RepeatMode
{
    REPEAT_MODE_CLAMP,
    REPEAT_MODE_REPEAT,
    REPEAT_MODE_RANDOMIZE
};

// Despawning mode.
enum DespawnMode
{ 
    DESPAWN_MODE_NEVER
};

// Respawning mode.
enum RespawnMode
{ 
    RESPAWN_MODE_NEVER
};

// OAM layer.
enum OamLayer
{
    OAM_LAYER_35,
    OAM_LAYER_25,
    OAM_LAYER_15,
    OAM_LAYER_05,
    OAM_LAYER_NORMAL,
    OAM_LAYER_TOP
};

// Tile map.
struct OamTilemap
{
    std::string name;
    RepeatMode repeatMode;
    u32 width;
    u32 height;
};

// Object.
struct OamObject
{
    static std::map<u32, OamObject*> loadedObjects;

    u32 id;
    std::string name;
    TileMode tileMode;
    PlacePosition placePosition;
    std::string description;
    std::vector<OamTilemap> tilemaps;
};

// Preset.
struct OamPreset
{
    static std::map<u32, OamPreset*> loadedPresets;

    u32 id;
    std::string name;
    u32 behavior;
    u32 objectId;
    u8 dataFlag;
    u8 data[16];
    DespawnMode despawnMode;
    RespawnMode respawnMode;
    OamLayer layer;
    u16 interruptsFlag;
    std::string description;
};