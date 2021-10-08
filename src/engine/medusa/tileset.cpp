#include "tileset.h"
#include "../screenData.h"
#include <bit>
#include <cstdint>

using namespace std;
using namespace tinyxml2;

std::map<std::string, TilesetLoadedEntry> Tileset::loadedTilesets;

void Tileset::LoadTileset(const std::string& name)
{
    TilesetLoadedEntry e;
    e.refCount = 1;
    e.tileset = new Tileset();
    Asset::Load(e.tileset, name);
    loadedTilesets[name] = e;
}

Tileset* Tileset::GetTileset(const std::string& name)
{
    return loadedTilesets[name].tileset;
}

void Tileset::UnloadTileset(const std::string& name)
{
    TilesetLoadedEntry& e = loadedTilesets[name];
    e.refCount--;
    if (e.refCount <= 0)
    {
        e.tileset->Unload();
        delete e.tileset;
    }
    loadedTilesets.erase(name);
}

string Tileset::AssetFolderName()
{
    return "Tsb";
}

string Tileset::GetXMLExtension()
{
    return "tsx";
}

string Tileset::GetBINExtension()
{
    return "mtsb";
}

void Tileset::FromXML(const string& name)
{
    XMLDocument doc;
    doc.LoadFile(Asset::GetFilePath(this, name, true).c_str());
    XMLElement* root = doc.RootElement();
    tileWidth = (u16)root->IntAttribute("tilewidth");
    tileHeight = (u16)root->IntAttribute("tilewidth");
    numTiles = (u32)root->IntAttribute("tilecount");
    tilesPerRow = (u32)root->IntAttribute("columns");
    root = root->FirstChildElement();
    imagePath = root->Attribute("source");
    tex = ALoadTexture(Asset::assetFolder + AssetFolderName() + "/" + imagePath);
}

void Tileset::FromBIN(const std::string& name)
{
    GFile f = GFile(Asset::GetFilePath(this, name).c_str());
    if (f.ReadStrFixed(4) != "MTSB")
    {
        throw string("Invalid Medusa TileSet Binary!");
    }
    tileWidth = f.ReadU16();
    tileHeight = f.ReadU16();
    numTiles = f.ReadU32();
    tilesPerRow = f.ReadU32();
    imagePath = f.ReadStr();
    tex = ALoadTexture(Asset::assetFolder + AssetFolderName() + "/" + imagePath);
}

void Tileset::WriteXML(const std::string& destPath)
{

}

void Tileset::WriteBIN(const std::string& destPath)
{
    GFile f = GFile(destPath.c_str());
    f.Write("MTSB");
    f.Write(tileWidth);
    f.Write(tileHeight);
    f.Write(numTiles);
    f.Write(tilesPerRow);
    f.WriteNullTerminated(imagePath);
}

void Tileset::Unload()
{
    imagePath = "";
    AUnloadTexture(tex);
}

void Tileset::DrawTile(u32 tileId, int tileX, int tileY, float offX, float offY)
{
    ADrawTexture(tex, (float)(tileId % tilesPerRow * TILE_SIZE), (float)(tileId / tilesPerRow * TILE_SIZE), TILE_SIZE, TILE_SIZE, offX + tileX * TILE_SIZE, offY + tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}