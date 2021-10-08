#pragma once

#include "../types.h"

enum AudioEncoding : u8
{
    PCM8,
    PCM16,
    IMAADPCM
};

struct MAudioStream
{
    u32 sampleRate;
    u8 numChannels;
    u8 numTracks;
    AudioEncoding encoding;
    u8 numLoops;
    u8* data;
    u16 blockSize;
    u16 lastBlockSize;
    u16 blockSamples;
    u16 lastBlockSamples;
    u32 numBlocks;
    // TODO: TRACKS AND LOOPS!!!
};