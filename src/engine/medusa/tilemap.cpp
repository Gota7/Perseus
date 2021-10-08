#include "tilemap.h"
#include "tileset.h"
#include <sstream>

using namespace std;
using namespace tinyxml2;

std::map<std::string, TilemapLoadedEntry> Tilemap::loadedTilemaps;

void Tilemap::LoadTilemap(const std::string& name)
{
    TilemapLoadedEntry e;
    e.refCount = 1;
    e.tilemap = new Tilemap();
    Asset::Load(e.tilemap, name);
    loadedTilemaps[name] = e;
}

Tilemap* Tilemap::GetTilemap(const std::string& name)
{
    return loadedTilemaps[name].tilemap;
}

void Tilemap::UnloadTilemap(const std::string& name)
{
    TilemapLoadedEntry& e = loadedTilemaps[name];
    e.refCount--;
    if (e.refCount <= 0)
    {
        e.tilemap->Unload();
        delete e.tilemap;
    }
    loadedTilemaps.erase(name);
}

string Tilemap::ReplaceStr(string& str, const string& from, const string& to)
{
    while(str.find(from) != string::npos)
        str.replace(str.find(from), from.length(), to);
    return str;
}

string Tilemap::AssetFolderName()
{
    return "Tmb";
}

string Tilemap::GetXMLExtension()
{
    return "tmx";
}

string Tilemap::GetBINExtension()
{
    return "mtmb";
}

void Tilemap::FromXML(const string& name)
{
    XMLDocument doc;
    doc.LoadFile(Asset::GetFilePath(this, name, true).c_str());
    XMLElement* root = doc.RootElement();
    width = (u32)root->IntAttribute("width");
    height = (u32)root->IntAttribute("height");
    XMLElement* child = root->FirstChildElement();
    while (child != NULL)
    {
        if (string(child->Name()) == "tileset")
        {
            TilesetEntry t;
            t.name = AGetFileNameWithoutExtension(child->Attribute("source"));
            t.startingTileId = (u32)child->IntAttribute("firstgid");
            Tileset::LoadTileset(t.name);
            t.tileset = Tileset::GetTileset(t.name);
            tilesets.push_back(t);
        }
        else if (string(child->Name()) == "layer")
        {
            LayerEntry e;
            e.name = child->Attribute("name");
            string rawData = child->FirstChildElement()->GetText();
            rawData = ReplaceStr(rawData, "\r", "");
            rawData = ReplaceStr(rawData, "\n", "");
            rawData = ReplaceStr(rawData, ",", " ");
            stringstream ss = stringstream(rawData);
            int temp;
            while (ss >> temp)
            {
                u8 tileset = 0;
                for (u8 i = 0; i < tilesets.size(); i++)
                {
                    if (temp >= tilesets[i].startingTileId)
                    {
                        tileset = i;
                    }
                    else
                    {
                        break;
                    }
                }
                e.tiles.push_back((temp - tilesets[tileset].startingTileId + 1) | (tileset << 16));
            }
            layers.push_back(e);
        }
        child = child->NextSiblingElement();
    }
}

void Tilemap::FromBIN(const std::string& name)
{
    GFile f = GFile(Asset::GetFilePath(this, name).c_str());
    if (f.ReadStrFixed(4) != "MTMB")
    {
        throw string("Invalid Medusa TileMap Binary!");
    }
    width = f.ReadU32();
    height = f.ReadU32();
    u8 numTilesets = f.ReadU8();
    tilesets.resize(numTilesets);
    for (u8 i = 0; i < numTilesets; i++)
    {
        tilesets[i].startingTileId = f.ReadU32();
        tilesets[i].name = f.ReadStr();
        Tileset::LoadTileset(tilesets[i].name);
        tilesets[i].tileset = Tileset::GetTileset(tilesets[i].name);
    }
    u8 numLayers = f.ReadU8();
    layers.resize(numLayers);
    for (u8 i = 0; i < numLayers; i++)
    {
        layers[i].name = f.ReadStr();
        layers[i].tiles.reserve(width * height);
        u32 totalTiles = 0;
        while (totalTiles < width * height)
        {
            u16 numTiles = f.ReadU16();
            u32 tileId = f.ReadU32();
            auto& tiles = layers[i].tiles;
            tiles.insert(tiles.end(), numTiles, tileId);
            totalTiles += numTiles;
        }
    }
}

void Tilemap::WriteXML(const std::string& destPath)
{

}

void Tilemap::WriteBIN(const std::string& destPath)
{
    GFile f = GFile(destPath.c_str());
    f.Write("MTMB");
    f.Write(width);
    f.Write(height);
    f.Write((u8)tilesets.size());
    for (u8 i = 0; i < tilesets.size(); i++)
    {
        f.Write(tilesets[i].startingTileId);
        f.WriteNullTerminated(tilesets[i].name);
    }
    f.Write((u8)layers.size());
    for (u8 i = 0; i < layers.size(); i++)
    {
        f.WriteNullTerminated(layers[i].name);
        u32 numWritten = 0;
        for (u32 j = 0; j < layers[i].tiles.size() && numWritten < width * height; j++)
        {
            u16 numTiles = 1;
            u32 id = layers[i].tiles[j];
            numWritten++;
            while (numTiles < 0xFFFF && numWritten < width * height && layers[i].tiles[j + numTiles] == id)
            {
                numTiles++;
                numWritten++;
            }
            f.Write(numTiles);
            f.Write(id);
            j += numTiles - 1;
        }
    }
}

void Tilemap::Unload()
{
    for (int i = 0; i < tilesets.size(); i++)
    {
        Tileset::UnloadTileset(tilesets[i].name);
    }
    tilesets.clear();
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i].tiles.clear();
    }
    layers.clear();
}

void Tilemap::Draw(u8 layerNum, float offX, float offY)
{
    for (u32 x = 0; x < width; x++)
    {
        for (u32 y = 0; y < height; y++)
        {
            u32 rawId = layers[layerNum].tiles[y * width + x];
            u16 id = rawId & 0xFFFF;
            u8 tileset = (rawId >> 16) & 0xFF;
            if (id == 0)
                continue;
            Tileset* t = tilesets[tileset].tileset;
            t->DrawTile(id - 1, x, y, offX, offY);
        }
    }
}