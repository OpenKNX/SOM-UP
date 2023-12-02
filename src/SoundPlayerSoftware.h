#pragma once

#include "AudioFileSourceFunction.h"
#include "AudioFileSourceLittleFS.h"
#include "AudioGeneratorMP3.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputSOM.h"
#include "SoundPlayer.h"
#include <map>

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
    inline float generateTone(const float time);

    uint8_t toneSequenceRepeats = 0;
    uint8_t toneSequenceRepeatPause = 0;
    uint16_t toneSequenceDuration = 0;
    std::map<uint16_t, uint16_t> toneSequence = {};

    void loadToneGenerator(uint8_t sequenz);
    void calcToneGeneratorDuration();

  public:
    void setup() override;
    void loop() override;
    const char *playTypeName() override;

#ifdef OPENKNX_DEBUG
    static void callbackStatus(void *cbData, int code, const char *string);
#endif
};