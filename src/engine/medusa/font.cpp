#include "font.h"
#include "../backend.h"

using namespace std;
using namespace tinyxml2;

string MFont::AssetFolderName()
{
    return "Fnt";
}

string MFont::GetXMLExtension()
{
    return "xml";
}

string MFont::GetBINExtension()
{
    return "mfnt";
}

void MFont::FromXML(const string& name)
{

    // General info.
    XMLDocument doc;
    doc.LoadFile(Asset::GetFilePath(this, name, true).c_str());
    XMLElement* root = doc.RootElement();
    imagePath = root->Attribute("image");
    tex = ALoadTexture(Asset::assetFolder + AssetFolderName() + "/" + imagePath);
    tileWidth = (u16)root->IntAttribute("tilewidth");
    tileHeight = (u16)root->IntAttribute("tilewidth");
    numTiles = (u32)root->IntAttribute("tilecount");
    tilesPerRow = (u32)root->IntAttribute("columns");
    lineAdvance = (s16)root->IntAttribute("lineadvance");

    // Get symbols.
    XMLElement* child = root->FirstChildElement();
    u32 tileNum = 0;
    while (child != NULL)
    {
        if (string(child->Name()) == "chars")
        {
            XMLElement* currSym = child->FirstChildElement();
            while (currSym != NULL)
            {
                MFontCharInfo cI;
                cI.tileOff = tileNum++;
                chars[currSym->Attribute("symbol")[0]] = cI;
                currSym = currSym->NextSiblingElement();
            }
        }
        child = child->NextSiblingElement();
    }

}

void MFont::FromBIN(const std::string& name)
{

}

void MFont::WriteXML(const std::string& destPath)
{
    
}

void MFont::WriteBIN(const std::string& destPath)
{
    
}

void MFont::Unload()
{
    AUnloadTexture(tex);
}

void MFont::DrawChar(char c, float x, float y, AColor color)
{
    MFontCharInfo* cI; 
    if (chars.find(c) != chars.end())
    {
        cI = &chars[c];
    }
    else
    {
        cI = &chars[0];
    }
    float tileX = (cI->tileOff % tilesPerRow) * tileWidth;
    float tileY = (cI->tileOff / tilesPerRow) * tileHeight;
    ADrawTexture(tex, tileX, tileY, tileWidth, tileHeight, x + cI->xOff, y + cI->yOff, tileWidth, tileHeight, ZERO_VEC, 0, color);
}

void MFont::DrawString(std::string str, float x, float y, AColor color, float lineWidthMax)
{
    float currXOff = 0;
    float currYOff = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char c = str.c_str()[i];
        MFontCharInfo* cI; 
        if (chars.find(c) != chars.end())
        {
            cI = &chars[c];
        }
        else
        {
            cI = &chars[0];
        }
        float newXOff = currXOff + cI->spacing + tileWidth;
        if (newXOff > lineWidthMax)
        {
            currXOff = 0;
            currYOff += lineAdvance + tileHeight;
        }
        DrawChar(c, x + currXOff, y + currYOff, color);
        currXOff = newXOff;
    }
}