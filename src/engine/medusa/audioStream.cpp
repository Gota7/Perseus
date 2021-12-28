#include "audioStream.h"
#include "../backend.h"

using namespace std;
using namespace tinyxml2;

const s32 MAudioStream::BLOCK_SIZE = 4096;

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
    
    // General info.
    XMLDocument doc;
    doc.LoadFile(Asset::GetFilePath(this, name, true).c_str());
    XMLElement* root = doc.RootElement();
    string wavPath = root->Attribute("wav");
    gFile = GFile((Asset::assetFolder + AssetFolderName() + "/" + wavPath).c_str());
    gFile.position = 0x10;
    u32 fmtSize = gFile.ReadU32();
    u16 fmt = gFile.ReadU16();
    if (fmt != 0x1 && fmt != 0x11)
    {
        printf("INVALID WAVE FORMAT (UNKNOWN FMT MARKER)!\n");
        return;
    }
    numChannels = (u8)gFile.ReadU16();
    sampleRate = gFile.ReadU32();
    gFile.position += 6;
    u16 sampleSize = gFile.ReadU16();
    switch (sampleSize)
    {
        case 4:
            encoding = AudioEncoding::IMAADPCM;
            break;
        case 8:
            encoding = AudioEncoding::PCM8;
            break;
        case 16:
            encoding = AudioEncoding::PCM16;
            break;
        default:
            printf("INVALID WAVE FORMAT (BAD SAMPLE SIZE)!\n");
            return;
    }
    
    // Read loops and tracks.
    numTracks = 0;
    numLoops = 0;
    XMLElement* child = root->FirstChildElement();
    while (child != NULL)
    {
        if (string(child->Name()) == "loop")
        {
            Loop l;
            l.startSample = child->IntAttribute("start");
            l.endSample = child->IntAttribute("end");
            l.numRepetitions = child->IntAttribute("numLoops");
            numLoops++;
            loops.push_back(l);
        }
        else if (string(child->Name()) == "track")
        {
            Track t;
            string rawChannels = child->Attribute("channels");
            numTracks++;
            tracks.push_back(t);
        }
        child = child->NextSiblingElement();
    }

    // Data info.
    gFile.position = 0x14 + fmtSize;
    if (gFile.ReadStrFixed(4) != "data")
    {
        printf("INVALID WAVE FORMAT (BAD DATA BLOCK)!\n");
        return;
    }
    u32 dataSize = gFile.ReadU32();
    switch (encoding)
    {
        case AudioEncoding::IMAADPCM:
            numSamples = dataSize / numChannels * 2;
            break;
        case AudioEncoding::PCM8:
            numSamples = dataSize / numChannels;
            break;
        case AudioEncoding::PCM16:
            numSamples = dataSize / numChannels / 2;
            break;
    }
    dataOff = gFile.position;
    stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 8 : 16, numChannels);
    ASetAudioStreamVolume(stream, volume);
    ASetAudioStreamPitch(stream, pitch);

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
        loops[i].startSample = gFile.ReadU32();
        loops[i].endSample = gFile.ReadU32();
        loops[i].numRepetitions = gFile.ReadU8();
    }

    // We are at the data offset.
    dataOff = (u32)gFile.position;
    stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 8 : 16, numChannels);
    ASetAudioStreamVolume(stream, volume);
    ASetAudioStreamPitch(stream, pitch);

}

void MAudioStream::WriteXML(const std::string& destPath)
{
    
}

void MAudioStream::WriteBIN(const std::string& destPath)
{

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
        gFile.position = dataOff;
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
}

void MAudioStream::Update()
{

    // Check to see if more samples are needed.
    if (!AIsAudioStreamPlaying(stream)) return;
    if (AIsAudioStreamProcessed(stream))
    {
        int read = ReadSamples(BLOCK_SIZE);
        if (read == 0) Stop();
    }

}

void MAudioStream::Unload()
{
    gFile.Close();
    AUnloadAudioStream(stream);
}

int MAudioStream::ReadSamples(int toRead)
{

    // Find end.
    s32 start = currSample;
    s32 end = currSample + toRead;
    bool forceNonzeroRet = false;
    for (int i = 0; i < numLoops; i++)
    {
        Loop* l = &loops[i];
        if (end > l->endSample && l->numRepetitions != 255)
        {
            end = l->endSample;
            if (l->numRepetitions != 0)
            {
                l->numRepetitions--;
                if (l->numRepetitions == 0) l->numRepetitions = 255;
            }
            currSample = l->startSample;
            forceNonzeroRet = true;
            break;
        }
    }
    PositionReaderAtSample(start);
    u32 size = (end - start) * numChannels;
    if (encoding == PCM16) size *= 2;
    if (encoding == IMAADPCM) size /= 2;
    void* buff = malloc(size);
    gFile.Read(buff, size);
    AUpdateAudioStream(stream, buff, end - start);
    free(buff);
    if (!forceNonzeroRet) currSample = end;
    return forceNonzeroRet ? 1 : (end - start);

}

void MAudioStream::PositionReaderAtSample(int sampleNum)
{
    u32 off = 0;
    switch (encoding)
    {
        case AudioEncoding::IMAADPCM:
            // TODO!!!
            break;
        case AudioEncoding::PCM8:
            off = sampleNum * numChannels;
            break;
        case AudioEncoding::PCM16:
            off = sampleNum * numChannels * 2;
            break;
    }
    gFile.position = dataOff + off;
}