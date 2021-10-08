#pragma once

#include "../backend.h"
#include "../types.h"
#include "../gbin/gfile.h"
#include "../tinyxml2/tinyxml2.h"
#include <string>

// Medusa Asset.
struct Asset
{

    // Asset folder.
    static std::string assetFolder;

    // Load an asset.
    static void Load(Asset* asset, std::string assetName, bool preferBinary = true);

    // Get the full path to the asset.
    static std::string GetFilePath(Asset* asset, std::string assetName, bool xml = false);

    // Get the folder name of the asset.
    virtual std::string AssetFolderName() { return ""; }

    // Get the XML extension.
    virtual std::string GetXMLExtension() { return ""; }

    // Get the binary extension.
    virtual std::string GetBINExtension() { return ""; }

    // Read an asset from XML.
    virtual void FromXML(const std::string& name) {}

    // Read an asset from binary.
    virtual void FromBIN(const std::string& name) {}

    // Write an XML given a path.
    virtual void WriteXML(const std::string& destPath) {}

    // Write a binary file given a path.
    virtual void WriteBIN(const std::string& destPath) {}

    // Unload the asset.
    virtual void Unload() {}

};