#pragma once

#ifndef HARDWARE_PLAYER
    #include "AudioFileSourceLittleFS.h"
    #include "AudioGeneratorMP3.h"
    #include "AudioOutputSOM.h"
    #include "SoundPlayer.h"

class SoundPlayerSoftware : public SoundPlayer
{
  private:
    AudioFileSource *audioSource = nullptr;
    AudioGeneratorMP3 *audioGenerator = nullptr;
    AudioOutputSOM *audioOutput;

    void playNextPlay() override;
    void playFileNumber(uint16_t file) override;

    void processStatus();
    void stopCurrentPlay();

    void processStatusStopped() override;

  public:
    void setup() override;
    void loop() override;

    // static void callbackStatus(void *cbData, int code, const char *string);
};
#endif