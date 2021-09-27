#pragma once

#include "asset.h"
#include <map>

/*
* TMX Specification
* 
* <?xml version="1.0" encoding="UTF-8"?>
* <map version="1.4" tiledversion="1.4.1" orientation="orthogonal" renderorder="left-down" width="27" height="15" tilewidth="16" tileheight="16" infinite="0" nextlayerid="7" nextobjectid="4">
*  <tileset firstgid="1" source="../tsb/Ruins.tsx"/>
*  <tileset firstgid="369" source="../tsb/Kcl.tsx"/>
*  <layer id="2" name="BG3" width="27" height="15">
*   <data encoding="csv">
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,120,121,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,143,144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,122,123,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,145,146,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,0,0,124,150,127,0,0,0,0,0,0,0,0,0,0,0,0,0,0,352,0,354,0,0,0,0,
*    0,0,124,147,116,150,127,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*    0,124,147,118,116,119,150,125,126,125,125,125,126,125,125,125,126,126,125,126,126,126,126,126,125,125,126,
*    0,122,139,139,139,141,140,139,142,117,141,117,119,139,139,116,140,119,119,139,116,139,142,118,116,140,142,
*    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
*   </data>
*  </layer>
* </map
* 
*/

/*
* MTMB Specification
* 
* char[4] magic = "MTMB"
* u32 width
* u32 height
* u8 numTilesets
* Tileset[numTilesets]
* u8 numLayers
* Layer[numLayers]
* 
* Tileset {
*  u32 startingTileId
*  string tilesetName
* }
* 
* Layer {
*  string name
*  { u16 numTiles, u32 tileIdWithTileset }[] RLECompressedTiles
* }
* 
*/

// Forward declare.
struct Tileset;
struct Tilemap;
struct TilemapLoadedEntry
{
    Tilemap* tilemap;
    int refCount;
};

// Tile layers.
enum TilemapLayers
{
    LAYER_BG3,
    LAYER_BG2,
    LAYER_BG1,
    LAYER_KCL,
    LAYER_OV
};

// Tileset entries.
struct TilesetEntry
{
    u32 startingTileId;
    std::string name;
    Tileset* tileset;
};

// Layer entries.
struct LayerEntry
{
    std::string name;
    std::vector<u32> tiles;
};

// Tilemap asset.
struct Tilemap : Asset
{

    // Data.
    u32 width;
    u32 height;
    std::vector<TilesetEntry> tilesets;
    std::vector<LayerEntry> layers;

    // Map of tilemaps.
private:
    static std::map<std::string, TilemapLoadedEntry> loadedTilemaps;
public:
    static void LoadTilemap(const std::string& name);
    static Tilemap* GetTilemap(const std::string& name);
    static void UnloadTilemap(const std::string& name);

    // Implement.
    static std::string ReplaceStr(std::string& str, const std::string& from, const std::string& to);
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    void Unload();

    // Tilemap stuff.
    void Draw(u8 layerNum, float offX = 0, float offY = 0);

};