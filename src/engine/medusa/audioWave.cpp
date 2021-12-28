#include "audioWave.h"
#include "../backend.h"

using namespace std;
using namespace tinyxml2;

string MAudioWave::AssetFolderName()
{
    return "Wav";
}

string MAudioWave::GetXMLExtension()
{
    return "xml";
}

string MAudioWave::GetBINExtension()
{
    return "mwav";
}

void MAudioWave::FromXML(const string& name)
{
    
    // General info.
    XMLDocument doc;
    doc.LoadFile(Asset::GetFilePath(this, name, true).c_str());
    XMLElement* root = doc.RootElement();
    string wavPath = root->Attribute("wav");
    poolSize = root->IntAttribute("poolSize");
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
    XMLElement* child = root->FirstChildElement();
    if (child != NULL)
    {
        if (string(child->Name()) == "loop")
        {
            loopStart = child->IntAttribute("start");
            loopEnd = child->IntAttribute("end");
            loops = true;
        }
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
    waveInfo = new RuntimeWaveInfo[poolSize];
    for (int i = 0; i < poolSize; i++)
    {
        waveInfo[i].stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 8 : 16, numChannels);
    }

}

void MAudioWave::FromBIN(const std::string& name)
{

    // General data.
    gFile = GFile(Asset::GetFilePath(this, name).c_str());
    if (gFile.ReadStrFixed(4) != "MSTM")
    {
        throw string("Invalid Medusa STreaM Binary!");
    }
    sampleRate = gFile.ReadU32();
    numChannels = gFile.ReadU8();
    encoding = (AudioEncoding)gFile.ReadU8();
    loops = gFile.ReadU8();
    poolSize = gFile.ReadU8();
    numSamples = gFile.ReadU32();
    loopStart = gFile.ReadU32();
    loopEnd = gFile.ReadU32();

    // We are at the data offset.
    dataOff = (u32)gFile.position;
    waveInfo = new RuntimeWaveInfo[poolSize];
    for (int i = 0; i < poolSize; i++)
    {
        waveInfo[i].stream = ALoadAudioStream(sampleRate, encoding == AudioEncoding::PCM8 ? 8 : 16, numChannels);
    }

}

void MAudioWave::WriteXML(const std::string& destPath)
{
    
}

void MAudioWave::WriteBIN(const std::string& destPath)
{

}

f32 MAudioWave::Volume(WaveInstance* instance)
{
    if (Dead(instance)) return -1;
    return waveInfo[instance->handle].volume;
}

f32 MAudioWave::Pitch(WaveInstance* instance)
{
    if (Dead(instance)) return -1;
    return waveInfo[instance->handle].pitch;
}

void MAudioWave::SetVolume(WaveInstance* instance, f32 volume)
{
    if (Dead(instance)) return;
    waveInfo[instance->handle].volume = volume;
}

void MAudioWave::SetPitch(WaveInstance* instance, f32 pitch)
{
    if (Dead(instance)) return;
    waveInfo[instance->handle].pitch = pitch;
}

WaveInstance MAudioWave::Play()
{

    // Calculate the handle and get wave instance.
    s32 handle = currId % poolSize;
    RuntimeWaveInfo* r = &waveInfo[handle];

    // Stop the wave, and start playing.
    Stop(r);
    APlayAudioStream(r->stream);

    // Return the new wave instance.
    WaveInstance ret;
    ret.handle = handle;
    ret.id = currId++;
    return ret;

}

void MAudioWave::Play(WaveInstance* instance)
{
    if (Dead(instance)) return;
    RuntimeWaveInfo* r = &waveInfo[instance->handle];
    if (r->paused)
    {
        AResumeAudioStream(r->stream);
        r->paused = false;
    }
    else
    {
        APlayAudioStream(r->stream);
    }
}

void MAudioWave::Pause(WaveInstance* instance)
{
    if (Dead(instance)) return;
    RuntimeWaveInfo* r = &waveInfo[instance->handle];
    APauseAudioStream(r->stream);
    r->paused = true;
}

void MAudioWave::Stop(WaveInstance* instance)
{
    if (Dead(instance)) return;
    RuntimeWaveInfo* r = &waveInfo[instance->handle];
    Stop(r);
}

bool MAudioWave::Dead(WaveInstance* instance)
{
    return instance->id < (s64)currId - poolSize;
}

void MAudioWave::Update()
{

    // For each audio stream, check to see if the buffer is processed.
    for (int i = 0; i < poolSize; i++)
    {
        RuntimeWaveInfo* r = &waveInfo[i];
        if (!AIsAudioStreamPlaying(r->stream)) continue;
        if (AIsAudioStreamProcessed(r->stream))
        {
            int read = ReadSamples(r, MAudioStream::BLOCK_SIZE);
            if (read == 0) Stop(r);
        }
    }

}

void MAudioWave::Unload()
{
    gFile.Close();
    for (int i = 0; i < poolSize; i++)
    {
        AUnloadAudioStream(waveInfo[i].stream);
    }
    delete[] waveInfo;
}

void MAudioWave::Stop(RuntimeWaveInfo* r)
{
    AStopAudioStream(r->stream);
    r->paused = false;
    r->currSample = 0;
}

int MAudioWave::ReadSamples(RuntimeWaveInfo* r, int toRead)
{

    // Find end.
    s32 start = r->currSample;
    s32 end = r->currSample + toRead;
    bool forceNonzeroRet = false;
    if (loops)
    {
        if (end > loopEnd)
        {
            end = loopEnd;
            r->currSample = loopStart;
            forceNonzeroRet = true;
        }
    }
    if (end > numSamples) end = numSamples;
    PositionReaderAtSample(start);
    u32 size = (end - start) * numChannels;
    if (encoding == PCM16) size *= 2;
    if (encoding == IMAADPCM) size /= 2;
    void* buff = malloc(size);
    gFile.Read(buff, size);
    AUpdateAudioStream(r->stream, buff, end - start);
    free(buff);
    if (!forceNonzeroRet) r->currSample = end;
    return forceNonzeroRet ? 1 : (end - start);

}

void MAudioWave::PositionReaderAtSample(int sampleNum)
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