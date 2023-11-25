#pragma once

#include "AudioFileSourceFunction.h"
#include "AudioFileSourceLittleFS.h"
#include "AudioGeneratorMP3.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputSOM.h"
#include "SoundPlayer.h"

class SoundPlayerSoftware : public SoundPlayer
{
  private:
    AudioFileSource *_audioSource = nullptr;
    AudioGenerator *_audioGenerator = nullptr;
    AudioOutputSOM *_audioOutput = nullptr;

    void playNextPlay() override;

    void processStatus();
    void stopCurrentPlay();

    void processStatusStopped() override;

  public:
    void setup() override;
    void loop() override;
    const char* playTypeName() override;

#ifdef OPENKNX_DEBUG
    static void callbackStatus(void *cbData, int code, const char *string);
#endif
};