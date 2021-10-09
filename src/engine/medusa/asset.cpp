#include "asset.h"
#include "../backend.h"

using namespace std;

string Asset::assetFolder = AGetWorkingDirectory() + "/Res/";;

void Asset::Load(Asset* asset, string assetName, bool preferBinary)
{
    
    // Get existence.
    string pathWithoutExtension = asset->AssetFolderName() + "/" + assetName;
    bool binExists = GFile::FileExists((assetFolder + pathWithoutExtension + "." + asset->GetBINExtension()).c_str());
    bool xmlExists = GFile::FileExists((assetFolder + pathWithoutExtension + "." + asset->GetXMLExtension()).c_str());

    // Binary.
    if (binExists && (preferBinary || !xmlExists))
    {
        asset->FromBIN(assetName);
    }

    // XML.
    else if (xmlExists)
    {
        asset->FromXML(assetName);
    }

    // Doesn't exist.
    else
    {
        printf("%s\n", ("Medusa content file \"" + pathWithoutExtension + "\" with \"" + asset->GetXMLExtension() + "\" or \"" + asset->GetBINExtension() + "\" extension does not exist.").c_str());
    }

}

string Asset::GetFilePath(Asset* asset, std::string assetName, bool xml)
{
    return Asset::assetFolder + asset->AssetFolderName() + "/" + assetName + "." + (xml ? asset->GetXMLExtension() : asset->GetBINExtension());
}