#pragma once
#include <Arduino.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

class SoundPlayer
{
  public:
    struct Play
    {
        uint16_t file = 0;
        uint8_t volume = 0;
        uint16_t repeats = 1;
        uint32_t duration = 0;
        uint32_t playMillis = 0;
        uint32_t playingMillis = 0;
    };

  protected:
    mutex_t _mutex;

    bool _powerSave = false;
    bool _playing = false;
    bool _stopping = false;

    Play _currentPlay;
    Play _nextPlay;

    virtual void powerOff();
    virtual void powerOn();

    virtual void processDuration();
    virtual void playNextPlay() = 0;
    virtual void stopCurrentPlay() = 0;
    virtual void processStopping();
    virtual void processNextPlay();
    virtual void processCheckCurrentPlay(uint16_t delay);

  public:
    SoundPlayer();
    virtual std::string logPrefix();
    virtual void savePower();
    virtual void restorePower();
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual void stop();
    virtual void setInitialVolume(uint8_t volume) { (void)volume; };
    virtual void play(uint16_t sound, uint8_t volume, uint32_t repeats = 0, uint32_t duration = 0);
    virtual const char* playTypeName();

    virtual void processStatusStopped();
    virtual void processStatusPlaying();
};