#ifndef HARDWARE_PLAYER
    #include "SoundPlayerSoftware.h"
    #include "OpenKNX/Log/VirtualSerial.h"
    #include "SoundModule.h"

void SoundPlayerSoftware::playNextPlay()
{
    audioOutput->SetVolume(_nextPlay.volume);

    // play file
    playFileNumber(_nextPlay.file);
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

    audioOutput = new AudioOutputSOM();
    audioOutput->SetVolume(0);
    audioOutput->SetOutputModeMono(true);
    audioGenerator = new AudioGeneratorMP3();

    // audioGenerator->RegisterStatusCB(SoundPlayerSoftware::callbackStatus, (void *)logPrefix().c_str());
    logTraceP("completed");
    logIndentDown();
}

// void SoundPlayerSoftware::callbackStatus(void *cbData, int code, const char *data)
// {
//     const char *ptr = reinterpret_cast<const char *>(cbData);
//     // Note that the string may be in PROGMEM, so copy it to RAM for printf
//     // char s1[64];
//     // strncpy_P(s1, string, sizeof(s1));
//     // s1[sizeof(s1) - 1] = 0;
//     // Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
//     // Serial.flush();
//     logInfo("ESP8266", "Status: %s (%i)", data, code);
// }

void SoundPlayerSoftware::loop()
{
    processDuration();
    processStopping();
    processStatus();
    processNextPlay();
}

void SoundPlayerSoftware::processStatus()
{
    if (!audioGenerator->isRunning()) return;

    processStatusPlaying();

    // next play or play is over
    if (_nextPlay.file > 0) stopCurrentPlay();

    if (!audioGenerator->loop())
    {
        if (_currentPlay.repeats > 0)
        {
            audioSource->seek(0, SEEK_SET);
            _currentPlay.repeats--;
            audioGenerator->loop();
        }
        else
        {
            stopCurrentPlay();
        }
    }
}

void SoundPlayerSoftware::playFileNumber(uint16_t file)
{
    // 10 Bytes /00000.MP3
    std::stringstream filePathBuild;
    filePathBuild << "/" << std::setfill('0') << std::setw(5) << std::to_string(file) << ".MP3";
    const std::string filePath = filePathBuild.str();

    powerOn();

    audioSource = new AudioFileSourceLittleFS(filePath.c_str());
    audioGenerator->begin(audioSource, audioOutput);
}

void SoundPlayerSoftware::stopCurrentPlay()
{
    if (audioGenerator->isRunning())
        audioGenerator->stop();

    processStatusStopped();
}

void SoundPlayerSoftware::processStatusStopped()
{
    SoundPlayer::processStatusStopped();
    powerOff();
}
#endif