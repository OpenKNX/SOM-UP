#pragma once
#include "DYPlayerArduino.h"
#include "SoundModule.h"
#include "hardware.h"
#include <iomanip>
#include <iostream>

class SoundControl;

class SoundPlayer
{

  struct Play
  {
    uint16_t file = 0;
    uint8_t volume = 0;
    uint32_t duration = 0;
    uint8_t repeats = 0;
    bool loop = false;
    uint32_t playMillis = 0;
    uint32_t playingMillis = 0;
  };

private:
  void processStatus();
  void requestStatus();
  void processDuration();
  void processStatusStopped();
  void processStatusPlaying();
  void processNextPlay();
  void play(Play &iPlay);
  char *getFilePath(uint16_t iFile);

  DY::Player mHardware;
  bool mPlaying = false;
  bool mStopping = false;

  Play mCurrentPlay;
  Play mNextPlay;
  uint32_t mPreviousMillis = 0;
  uint8_t mLastVolume = 0;

  bool mWaitForState = false;
  uint8_t mResponseStateBuffer[5];
  uint8_t mResponseStatePos = 0;

public:
  SoundPlayer();
  ~SoundPlayer();

  void setup();
  void play(uint16_t iSound, uint8_t iVolume, uint32_t iDuration = 0, bool iLoop = false);
  void stop();
  void loop();
  void setVolume(uint8_t iVolume);
};