#include "SoundPlayerSoftware.h"
#include "OpenKNX/Log/VirtualSerial.h"
#include "SoundModule.h"

void SoundPlayerSoftware::buildToneSequence(uint8_t _channelIndex)
{
    constexpr uint16_t offset = SOM_TG2Mode - SOM_TG1Mode;
    const uint16_t channelOffset = offset * _channelIndex;
    const uint8_t mode = (knx.paramByte(SOM_TG1Mode + channelOffset) & SOM_TG1ModeMask) >> SOM_TG1ModeShift;

    if (!mode) return;

    logDebugP("loadToneGenerator %i", _channelIndex);
    logIndentUp();
    toneSequenceRepeats = knx.paramByte(SOM_TG1Repeats + channelOffset);
    toneSequenceRepeatPause = knx.paramByte(SOM_TG1RepeatPause + channelOffset);

    logDebugP("ParamSOM_Index %i", _channelIndex);
    logDebugP("ParamSOM_Offset %i", offset);
    logDebugP("ParamSOM_ChannelOffset %i", channelOffset);
    logDebugP("ParamSOM_TG1Mode %i", mode);
    logDebugP("ParamSOM_TG1Repeats %i", toneSequenceRepeats);
    logDebugP("ParamSOM_TG1RepeatPause %i", toneSequenceRepeatPause);

    uint16_t time = 0;
    uint8_t max = (mode == 1) ? 1 : 9;
    for (size_t i = 0; i < max; i++)
    {
        uint8_t seqTime = knx.paramByte(SOM_TG1Duration1 + channelOffset + i);
        uint16_t seqFreq = knx.paramWord(SOM_TG1Frequency1 + channelOffset + (i * 2));
        if (seqTime > 0)
        {
            time += seqTime;
            toneSequence[time] = seqFreq;
            logDebugP("- %i %i %i", time, seqTime, seqFreq);
        }
    }
    logIndentDown();
}

void SoundPlayerSoftware::calcToneGeneratorDuration()
{
    if (toneSequence.size() == 0)
        toneSequenceDuration = 0;
    else
        toneSequenceDuration = (toneSequence.rbegin()->first * (toneSequenceRepeats + 1)) + (toneSequenceRepeats * toneSequenceRepeatPause);
}

void SoundPlayerSoftware::playNextPlay()
{
    _audioOutput->SetVolume(_nextPlay.volume);

    // powerOn();
    logInfoP("--- playNextPlay %i", _nextPlay.file);
    if (_audioGenerator != nullptr)
    {
        free(_audioGenerator);
        _audioGenerator = nullptr;
    }
    if (_audioSource != nullptr)
    {
        free(_audioSource);
        _audioSource = nullptr;
    }

    // Demo
    if (_nextPlay.file == 10000)
    {
        const char demo[] PROGMEM = "scale_up:d=32,o=5,b=100:c,c#,d#,e,f#,g#,a#,b,p";
        _audioSource = new AudioFileSourcePROGMEM(demo, strlen_P(demo));
        _audioGenerator = new AudioGeneratorRTTTL();
    }
    // special handling for generated ton.
    else if (_nextPlay.file >= 10000 && _nextPlay.file <= (10 + 10000))
    {
        // Reset
        toneSequence.clear();
        toneSequenceRepeats = 0;
        toneSequenceRepeatPause = 0;

        uint8_t _channelIndex = _nextPlay.file - 10000 - 1;

        buildToneSequence(_channelIndex);
        calcToneGeneratorDuration();

        AudioFileSourceFunction *currentAudioSource = new AudioFileSourceFunction(((float)toneSequenceDuration / 10), 1, 16000); // 8khz
        currentAudioSource->addAudioGenerators([this](const float time) {
            return this->generateTone(time);
        });

        _audioSource = currentAudioSource;
        _audioGenerator = new AudioGeneratorWAV();
    }
    else
    {
        char name[11] = {};
        if (findFile(_nextPlay.file, name))
        {
            logInfoP("File %s found for sound %i", name, _nextPlay.file);
            _audioSource = new AudioFileSourceLittleFS(name);
        }
        else
        {
            logErrorP("No file found for sound %i", _nextPlay.file);
        }

#ifdef OPENKNX_DEBUG
        // currentAudioGenerator->RegisterStatusCB(SoundPlayerSoftware::callbackStatus, (void *)"");
#endif
    }

    if(_audioSource == nullptr) return;

    set_sys_clock_khz(200000, true);
    if (_audioGenerator != nullptr)
        _audioGenerator->begin(_audioSource, _audioOutput);
}

void SoundPlayerSoftware::setup()
{
    logInfoP("init software player");
    logIndentUp();

#ifdef LOG_ESP8266AUDIO
    audioLogger = new OpenKNX::Log::VirtualSerial("ESP8266Audio");
#endif

    SoundPlayer::setup();
    // powerOff(); // will turn on only during play back

    _audioOutput = new AudioOutputSOM();
    _audioOutput->SetVolume(0);
    _audioOutput->SetOutputModeMono(true);

    logTraceP("completed");
    logIndentDown();
}

#ifdef OPENKNX_DEBUG
void SoundPlayerSoftware::callbackStatus(void *cbData, int code, const char *data)
{
    logDebug("ESP8266", "%s (%i)", data, code);
}
#endif

void SoundPlayerSoftware::loop()
{
    processCheckCurrentPlay(100);
    processDuration();
    processStopping();
    processStatus();
    processNextPlay();
}

void SoundPlayerSoftware::processStatus()
{
    if (_audioGenerator == nullptr) return;
    if (!_audioGenerator->isRunning()) return;

    processStatusPlaying();

    // next play or play is over
    if (_nextPlay.file > 0) stopCurrentPlay();

    if (!_audioGenerator->loop())
    {
        if (_currentPlay.repeats > 0)
        {
            _audioSource->seek(0, SEEK_SET);
            _currentPlay.repeats--;
            _audioGenerator->loop();
        }
        else
        {
            stopCurrentPlay();
        }
    }
}

void SoundPlayerSoftware::stopCurrentPlay()
{
    if (_audioGenerator->isRunning())
        _audioGenerator->stop();

    processStatusStopped();
}

void SoundPlayerSoftware::processStatusStopped()
{
    set_sys_clock_khz(F_CPU / 1000, true);
    SoundPlayer::processStatusStopped();
    // powerOff();
}

const char *SoundPlayerSoftware::playTypeName()
{
    return "Software (I2S)";
}

float SoundPlayerSoftware::generateTone(const float time)
{
    const uint16_t stepDuration = (uint16_t)(toneSequence.rbegin()->first + toneSequenceRepeatPause);
    uint16_t timeInt = (uint16_t)round(time * 10);

    // die if abfrage ist nötig, weil durch das float die werte ungenau sind.
    // das hätte zur folge dass die nächste wiederholung abgespielt wird obwohl jetzt ausgeschaltet wird.
    if (toneSequenceRepeats > 0 && timeInt / stepDuration <= toneSequenceRepeats)
    {
        timeInt %= stepDuration;
    }

    auto it = toneSequence.upper_bound(timeInt);

    if (it != toneSequence.end())
        return sin(TWO_PI * it->second * time); // generate sine wave
    else
        return 0;
}

bool SoundPlayerSoftware::findFile(uint16_t sound, char *name)
{
    memset(name, 0, 11);
    std::stringstream prefix;
    prefix << "/" << std::setfill('0') << std::setw(5) << std::to_string(sound);
    uint8_t prefixLen = prefix.str().size();

    // Prefix
    memcpy(name, prefix.str().c_str(), prefixLen);

    // Try suffixes
    memcpy(name + prefixLen, ".RTT", 4);
    if (LittleFS.exists(name))
    {
        _audioGenerator = new AudioGeneratorRTTTL();
        return true;
    }

    memcpy(name + prefixLen, ".WAV", 4);
    if (LittleFS.exists(name))
    {
        _audioGenerator = new AudioGeneratorWAV();
        return true;
    }

    memcpy(name + prefixLen, ".MP3", 4);
    if (LittleFS.exists(name))
    {
        _audioGenerator = new AudioGeneratorMP3();
        return true;
    }

    return false;
}