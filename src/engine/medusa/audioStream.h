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

// Runtime track info.
struct RuntimeTrackInfo
{
    f32 volume = 1.0;
    f32 pitch = 1.0;
    bool paused = false;
    u32 dataOff;
    void* stream;
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
    bool fromBin;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    f32 Volume(int trackNum);
    f32 Pitch(int trackNum);
    void SetVolume(int trackNum, f32 volume);
    void SetPitch(int trackNum, f32 pitch);
    void Play(int trackNum);
    void Pause(int trackNum);
    void Stop();
    void Update();
    void Unload();

private:
    RuntimeTrackInfo* trackInfo;
    int ReadSamples(RuntimeTrackInfo* r, int numSamples);
    void PositionReaderAtSample(int sampleNum);
};