#pragma once

#include "../types.h"
#include "asset.h"
#include "audioStream.h"
#include <vector>

// Wave instance.
struct WaveInstance
{
    s32 handle;
    u32 id;
};

// Runtime wave info.
struct RuntimeWaveInfo
{
    int currSample = 0;
    bool paused = false;
    f32 volume = 1.0;
    f32 pitch = 1.0;
    void* stream;
};

// Wave asset.
struct MAudioWave : Asset
{
    u32 sampleRate;
    u8 numChannels;
    AudioEncoding encoding;
    u8 loops;
    u8 poolSize;
    u32 numSamples;
    u32 loopStart;
    u32 loopEnd;

    // Run-time data.
    GFile gFile;
    u32 dataOff;
    u32 currId = 0;

    // Implement.
    std::string AssetFolderName();
    std::string GetXMLExtension();
    std::string GetBINExtension();
    void FromXML(const std::string& name);
    void FromBIN(const std::string& name);
    void WriteXML(const std::string& destPath);
    void WriteBIN(const std::string& destPath);
    f32 Volume(WaveInstance* instance);
    f32 Pitch(WaveInstance* instance);
    void SetVolume(WaveInstance* instance, f32 volume);
    void SetPitch(WaveInstance* instance, f32 pitch);
    WaveInstance Play();
    void Play(WaveInstance* instance);
    void Pause(WaveInstance* instance);
    void Stop(WaveInstance* instance);
    bool Dead(WaveInstance* instance);
    void Update();
    void Unload();

private:
    RuntimeWaveInfo* waveInfo;
    void Stop(RuntimeWaveInfo* r);
    int ReadSamples(RuntimeWaveInfo* r, int numSamples);
    void PositionReaderAtSample(int sampleNum);
};