#include "SoundPlayerSoftware.h"
#include "OpenKNX/Log/VirtualSerial.h"
#include "SoundModule.h"

void SoundPlayerSoftware::buildToneSequence(uint8_t _channelIndex)
{
    //if (!ParamTONE_ToneGeneratorMode) return;

    logDebugP("loadToneGenerator %i", _channelIndex);
    logIndentUp();
    toneSequenceRepeats = ParamTONE_ToneGeneratorRepeats;
    toneSequenceRepeatPause = ParamTONE_ToneGeneratorRepeatPause;
    logDebugP("ParamTONE_ToneGeneratorRepeats %i", ParamTONE_ToneGeneratorRepeats);
    logDebugP("ParamTONE_ToneGeneratorRepeatPause %i", ParamTONE_ToneGeneratorRepeatPause);
    logDebugP("ParamTONE_ToneGeneratorMode %i", ParamTONE_ToneGeneratorMode);

    uint16_t time = 0;
    uint8_t max = (ParamTONE_ToneGeneratorMode == 1) ? 1 : 9;
    for (size_t i = 0; i < max; i++)
    {
        uint8_t seqTime = knx.paramByte(TONE_ParamCalcIndex(TONE_ToneGeneratorDuration1 + i));
        uint16_t seqFreq = knx.paramWord(TONE_ParamCalcIndex(TONE_ToneGeneratorFrequency1 + i));
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

    // 10 Bytes /00000.MP3
    std::stringstream filePathBuild;
    filePathBuild << "/" << std::setfill('0') << std::setw(5) << std::to_string(_nextPlay.file) << ".MP3";
    const std::string filePath = filePathBuild.str();

    powerOn();

    if (_audioGenerator != nullptr) free(_audioGenerator);

    // special handling for generated ton.
    if (_nextPlay.file >= 10000 && _nextPlay.file <= (TONE_ChannelCount + 10000))
    {
        // Reset
        toneSequence.clear();
        toneSequenceRepeats = 0;
        toneSequenceRepeatPause = 0;

        uint8_t _channelIndex = _nextPlay.file - 10000 - 1;

        if (_nextPlay.file == 10000)
        {
            toneSequence[2] = 4000;
            toneSequence[3] = 0;
            toneSequence[5] = 4000;
            toneSequence[6] = 0;
            toneSequence[8] = 4000;
            toneSequence[9] = 0;
            toneSequence[16] = 4200;
        }
        else
        {
            buildToneSequence(_channelIndex);
        }

        calcToneGeneratorDuration();
        AudioGeneratorWAV *currentAudioGenerator = new AudioGeneratorWAV();

        AudioFileSourceFunction *currentAudioSource = new AudioFileSourceFunction(((float)toneSequenceDuration / 10), 1, 16000); // 8khz

        currentAudioSource->addAudioGenerators([this](const float time) {
            return this->generateTone(time);
        });

        _audioSource = currentAudioSource;
        _audioGenerator = currentAudioGenerator;
    }
    else
    {
        AudioGeneratorMP3 *currentAudioGenerator = new AudioGeneratorMP3();
        AudioFileSourceLittleFS *currentAudioSource = new AudioFileSourceLittleFS(filePath.c_str());

#ifdef OPENKNX_DEBUG
        currentAudioGenerator->RegisterStatusCB(SoundPlayerSoftware::callbackStatus, (void *)"");
#endif

        _audioSource = currentAudioSource;
        _audioGenerator = currentAudioGenerator;
    }

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
    powerOff(); // will turn on only during play back

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
    SoundPlayer::processStatusStopped();
    powerOff();
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