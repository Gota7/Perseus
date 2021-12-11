#pragma once

#include "../types.h"
#include "../color.h"
#include "asset.h"
#include "texture.h"
#include <map>

// Character entry.
struct MFontCharInfo
{
    u32 tileOff;
    s8 xOff = 0;
    s8 yOff = 0;
    s8 spacing = 0;
    std::map<char, s8> kernings;
};

// Medusa font.
struct MFont : Asset
{
    std::string imagePath;
    ATex tex;
    u16 tileWidth;
    u16 tileHeight;
    u32 numTiles;
    u32 tilesPerRow;
    s16 lineAdvance;
    std::map<char, MFontCharInfo> chars;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    void Unload();
    void DrawChar(char c, float x, float y, AColor color);
    void DrawString(std::string str, float x, float y, AColor color, float lineWidthMax = 1000);
};