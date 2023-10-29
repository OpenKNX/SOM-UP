#ifndef HARDWARE_PLAYER
    #include "SoundPlayerSoftware.h"
    #include "OpenKNX/Log/VirtualSerial.h"
    #include "SoundModule.h"

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
    if (_nextPlay.file == 10000)
    {
        AudioGeneratorWAV *currentAudioGenerator = new AudioGeneratorWAV();
        AudioFileSourceFunction *currentAudioSource = new AudioFileSourceFunction(5.);

        currentAudioSource->addAudioGenerators([&](const float time) {
            float v = sin(TWO_PI * 5000 * time); // generate sine wave
            v *= fmod(time, 1.f);                // change linear
            v *= 0.5;                            // scale
            return v;
        });

        _audioSource = currentAudioSource;
        _audioGenerator = currentAudioGenerator;
    }
    else
    {
        AudioGeneratorMP3 *currentAudioGenerator = new AudioGeneratorMP3();
        AudioFileSourceLittleFS *currentAudioSource = new AudioFileSourceLittleFS(filePath.c_str());

    #ifdef OPENKNX_DEBUG
        currentAudioGenerator->RegisterStatusCB(SoundPlayerSoftware::callbackStatus, (void *)logPrefix().c_str());
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

void SoundPlayerSoftware::callbackStatus(void *cbData, int code, const char *data)
{
    const char *ptr = reinterpret_cast<const char *>(cbData);
    // Note that the string may be in PROGMEM, so copy it to RAM for printf
    // char s1[64];
    // strncpy_P(s1, string, sizeof(s1));
    // s1[sizeof(s1) - 1] = 0;
    // Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
    // Serial.flush();
    logInfo("ESP8266", "Status: %s (%i)", data, code);
}

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
#endif