#pragma once

#include "../types.h"
#include "asset.h"
#include <vector>

// Audio encoding.
enum AudioEncoding : u8
{
    PCM8,
    PCM16,
    IMAADPCM
};

// Track.
struct Track
{
    u8 numChannels;
    std::vector<u8> channels;
};

// Loop info.
struct Loop
{
    u32 startOffset;
    u32 endOffset;
    u8 numRepetitions;
};

// Channel buffer.
typedef u8* ChannelBuffer[3];

// Stream asset.
struct MAudioStream : Asset
{
    u32 sampleRate;
    u8 numChannels;
    u8 numTracks;
    AudioEncoding encoding;
    u8 numLoops;
    u16 blockSize;
    u16 lastBlockSize;
    u16 blockSamples;
    u16 lastBlockSamples;
    u32 numBlocks;
    std::vector<Track> tracks;
    std::vector<Loop> loops;

    // Run-time data.
    GFile gFile;
    u32 dataOff;
    u8 currBuff = 0;
    ChannelBuffer* channelBuffers;
    bool isFullyLoaded;
    bool onLeftBuffer = true;
    u8 nextBlock = 0;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    void Unload();
    void LoadNextBlock(); // MUST ACCOUNT FOR CURRENT LOOP TOO!!!
};