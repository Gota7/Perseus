#include "audioStream.h"
#include "../backend.h"
#include "raylib.h"

using namespace std;
using namespace tinyxml2;

string MAudioStream::AssetFolderName()
{
    return "Stm";
}

string MAudioStream::GetXMLExtension()
{
    return "xml";
}

string MAudioStream::GetBINExtension()
{
    return "mstm";
}

void MAudioStream::FromXML(const string& name)
{
    isFullyLoaded = true;
}

void MAudioStream::FromBIN(const std::string& name)
{

    // General data.
    gFile = GFile(Asset::GetFilePath(this, name).c_str());
    if (gFile.ReadStrFixed(4) != "MSTM")
    {
        throw string("Invalid Medusa STreaM Binary!");
    }
    sampleRate = gFile.ReadU32();
    numChannels = gFile.ReadU8();
    numTracks = gFile.ReadU8();
    encoding = (AudioEncoding)gFile.ReadU8();
    numLoops = gFile.ReadU8();
    numSamples = gFile.ReadU32();

    // Tracks.
    tracks.resize(numTracks);
    for (int i = 0; i < numTracks; i++)
    {
        tracks[i].numChannels = gFile.ReadU8();
        tracks[i].channels.resize(tracks[i].numChannels);
        for (int j = 0; j < tracks[i].numChannels; j++)
        {
            tracks[i].channels[j] = gFile.ReadU8();
        }
    }

    // Loops.
    loops.resize(numLoops);
    for (int i = 0; i < numLoops; i++)
    {
        loops[i].startOffset = gFile.ReadU32();
        loops[i].endOffset = gFile.ReadU32();
        loops[i].numRepetitions = gFile.ReadU8();
    }

    // We are at the data offset.
    dataOff = (u32)gFile.position;
    isFullyLoaded = false;
    stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 8 : 16, numChannels);
    ASetAudioStreamVolume(stream, volume);
    ASetAudioStreamPitch(stream, pitch);

}

void MAudioStream::WriteXML(const std::string& destPath)
{
    
}

void MAudioStream::WriteBIN(const std::string& destPath)
{
    if (!isFullyLoaded) return;
}

f32 MAudioStream::Volume()
{
    return volume;
}

f32 MAudioStream::Pitch()
{
    return pitch;
}

void MAudioStream::SetVolume(f32 volume)
{
    this->volume = volume;
    ASetAudioStreamVolume(stream, volume);
}

void MAudioStream::SetPitch(f32 pitch)
{
    this->pitch = pitch;
    ASetAudioStreamPitch(stream, pitch);
}

void MAudioStream::Play()
{
    if (paused)
    {
        AResumeAudioStream(stream);
        paused = false;
    }
    else
    {
        APlayAudioStream(stream);
    }
}

void MAudioStream::Pause()
{
    APauseAudioStream(stream);
}

void MAudioStream::Stop()
{
    AStopAudioStream(stream);
    currSample = 0;
    gFile.position = dataOff;
}

void MAudioStream::Update()
{

    // Check to see if more samples are needed.
    if (!AIsAudioStreamPlaying(stream)) return;
    if (AIsAudioStreamProcessed(stream))
    {
        int read = ReadSamples(4096);
        if (read == 0) Stop();
    }

}

void MAudioStream::Unload()
{
    gFile.Close();
    AUnloadAudioStream(stream);
}

/*struct rlAudioBuffer {
    ma_data_converter converter;    // Audio data converter

    float volume;                   // Audio buffer volume
    float pitch;                    // Audio buffer pitch

    bool playing;                   // Audio buffer state: AUDIO_PLAYING
    bool paused;                    // Audio buffer state: AUDIO_PAUSED
    bool looping;                   // Audio buffer looping, always true for AudioStreams
    int usage;                      // Audio buffer usage mode: STATIC or STREAM

    bool isSubBufferProcessed[2];   // SubBuffer processed (virtual double buffer)
    unsigned int sizeInFrames;      // Total buffer size in frames
    unsigned int frameCursorPos;    // Frame cursor position
    unsigned int totalFramesProcessed;  // Total frames processed in this buffer (required for play timing)

    unsigned char *data;            // Data buffer, on music stream keeps filling

    rlAudioBuffer *next;             // Next audio buffer on the list
    rlAudioBuffer *prev;             // Previous audio buffer on the list
};*/

int MAudioStream::ReadSamples(int toRead)
{
    // Not reading.
    if (isFullyLoaded) return 0;
    int readSamples = 0;
    vector<u16> pcm16Buff;
    vector<u8> pcm8Buff;
    while (readSamples < toRead)
    {
        if (currSample >= numSamples) break;
        if (encoding == AudioEncoding::PCM8)
        {
            pcm8Buff.push_back(gFile.ReadU8());
        }
        else if (encoding == AudioEncoding::PCM16)
        {
            pcm16Buff.push_back(gFile.ReadU16());
        }
        else if (encoding == AudioEncoding::IMAADPCM)
        {

        }
        else
        {
            break;
        }
        currSample++;
        readSamples++;
    }
    AudioStream* as = (AudioStream*)stream;
    printf("%d\n", readSamples);
    AUpdateAudioStream(stream, encoding == AudioEncoding::PCM8 ? (void*)&pcm8Buff[0] : (void*)&pcm16Buff[0], readSamples);
    return readSamples;

}