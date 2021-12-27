#include "audioStream.h"
#include "../backend.h"

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
    GFile f = GFile(Asset::GetFilePath(this, name).c_str());
    if (f.ReadStrFixed(4) != "MSTM")
    {
        throw string("Invalid Medusa STreaM Binary!");
    }
    sampleRate = f.ReadU32();
    numChannels = f.ReadU8();
    numTracks = f.ReadU8();
    encoding = (AudioEncoding)f.ReadU8();
    numLoops = f.ReadU8();
    blockSize = f.ReadU16();
    lastBlockSize = f.ReadU16();
    blockSamples = f.ReadU16();
    lastBlockSamples = f.ReadU16();
    numBlocks = f.ReadU32();

    // Tracks.
    tracks.resize(numTracks);
    for (int i = 0; i < numTracks; i++)
    {
        tracks[i].numChannels = f.ReadU8();
        tracks[i].channels.resize(tracks[i].numChannels);
        for (int j = 0; j < tracks[i].numChannels; j++)
        {
            tracks[i].channels[j] = f.ReadU8();
        }
    }

    // Loops.
    loops.resize(numLoops);
    for (int i = 0; i < numLoops; i++)
    {
        loops[i].startOffset = f.ReadU32();
        loops[i].endOffset = f.ReadU32();
        loops[i].numRepetitions = f.ReadU8();
    }

    // We are at the data offset.
    dataOff = (u32)f.position;
    isFullyLoaded = false;
    stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 1 : 2, numChannels);
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

// TODO: LOOP INFO!!!
int MAudioStream::ReadSamples(int numSamples)
{
    // Not reading.
    if (!AIsAudioStreamPlaying(stream)) return 0;

    // TODO!!!
    int readSamples = 0;
    return readSamples;

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
}

void MAudioStream::Update()
{

    // Check to see if more samples are needed.
    if (AIsAudioStreamProcessed(stream))
    {
        
    }

}

void MAudioStream::Unload()
{
    gFile.Close();
    AUnloadAudioStream(stream);
}