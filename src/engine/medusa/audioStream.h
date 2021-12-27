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
    u32 startSample;
    u32 endSample;
    u8 numRepetitions;
};

// Stream asset.
struct MAudioStream : Asset
{
    static const s32 BLOCK_SIZE;
    u32 sampleRate;
    u8 numChannels;
    u8 numTracks;
    AudioEncoding encoding;
    u8 numLoops;
    u32 numSamples;
    std::vector<Track> tracks;
    std::vector<Loop> loops;

    // Run-time data.
    GFile gFile;
    u32 dataOff;
    int currSample = 0;
    bool paused = false;
    void* stream;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    f32 Volume();
    f32 Pitch();
    void SetVolume(f32 volume);
    void SetPitch(f32 pitch);
    void Play();
    void Pause();
    void Stop();
    void Update();
    void Unload();

private:
    f32 volume = 1.0;
    f32 pitch = 1.0;
    int ReadSamples(int numSamples);
};