#pragma once

#include "asset.h"
#include <map>
#include <memory>
#include <vector>

/*
* TSX Specification
* 
* <?xml version="1.0" encoding="UTF-8"?>
* <tileset version="1.4" tiledversion="1.4.1" name="Name" tilewidth="TileWidth" tileheight="TileHeight" tilecount="NumTiles" columns="NumColumns">
*  <image source="File.png" width="ImageWidth" height="ImageHeight"/>
* </tileset>
* 
*/

/*
* MTSB Specification
* 
* char[4] magic = "MTSB"
* u16 tileWidth
* u16 tileHeight
* u32 numTiles
* u32 tilesPerRow
* string imagePath
* Tile[numTiles] tiles          // Currently not implemented.
* 
* Tile {
*  u8 type { No Animation, No Animation With Type, Animated, Animated With Type }
*  string tileType if With Type
*  AnimationData animation if Animated
* }
* 
* AnimationData {
*  u32 numAnimations
*  u32[numAnimations] tileIds
*  u32[numAnimations] durations
*  u32 currentTile
*  u32 currentTime
* }
* 
*/

struct Tileset;
struct TilesetLoadedEntry
{
    Tileset* tileset;
    int refCount;
};

struct Tileset : Asset
{

    // Map of tilesets.
private:
    static std::map<std::string, TilesetLoadedEntry> loadedTilesets;
public:
    static void LoadTileset(const std::string& name);
    static Tileset* GetTileset(const std::string& name);
    static void UnloadTileset(const std::string& name);

    // Data.
    u16 tileWidth;
    u16 tileHeight;
    u32 numTiles;
    u32 tilesPerRow;
    std::string imagePath;
    Texture2D tex;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    void Unload();

    // Tileset stuff.
    void DrawTile(u32 tileId, int tileX, int tileY, float offX = 0, float offY = 0);

};