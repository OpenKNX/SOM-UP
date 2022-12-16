#pragma once
#include "DYPlayerArduino.h"
#include "SoundModule.h"
#include "hardware.h"
#include <iomanip>
#include <iostream>

class SoundControl;

class SoundPlayer
{

private:
  DY::Player mHardware;
  bool mStatus = false;
  bool mLastHardwareStatus = false;

  void processStatus();
  void requestStatus();
  uint32_t mPreviousMillis = 0;
  uint32_t mStartPlayMillis = 0;
  bool mWaitForPlaying = false;
  uint8_t mLastVolume = 0;
  DY::play_state_t lastState = DY::PlayState::Stopped;
  bool mWaitForState = false;
  uint8_t mResponseStateBuffer[5];
  uint8_t mResponseStatePos = 0;

public:
  SoundPlayer();
  ~SoundPlayer();

  void setup();
  void play(uint16_t iSound, uint8_t iVolume, bool iRepeat);
  void stop();
  void loop();
  void setVolume(uint8_t iVolume);
};