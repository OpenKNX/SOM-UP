#pragma once
#include "SoundModule.h"
#include "hardware.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

#define PLAYER_STATUS_WATCHDOG 1000
#define PLAYER_STATUS_PLAYING 1
#define PLAYER_STATUS_STOPPED 1
#define PLAYER_DATA_BEGIN 0xAA

class SoundControl;

class SoundPlayer
{

  struct Play
  {
    uint16_t file = 0;
    uint8_t volume = 0;
    uint32_t repeats = 1;
    uint32_t duration = 0;
    uint32_t playMillis = 0;
    uint32_t playingMillis = 0;
  };

private:
  void processStatus();
  void requestStatus();
  void watchdogStatus();
  void processDuration();
  void processStatusStopped();
  void processStatusPlaying();
  void processNextPlay();
  void play(Play &iPlay);

  bool mPlaying = false;
  bool mStopping = false;
  bool mLastRepeats = false;

  Play mCurrentPlay;
  Play mNextPlay;
  uint32_t mLastRequestStatus = 0;
  uint8_t mLastVolume = 0;

  bool mWaitForState = false;
  uint8_t mResponseStateBuffer[5];
  uint8_t mResponseStatePos = 0;

  uint8_t calcChecksum(uint8_t *data, uint8_t len);
  bool validateChecksum(uint8_t *data, uint8_t len);
  void sendData(uint8_t *data, uint8_t len);
  void setRepeats(uint16_t iRepeats = 1);
  void playFileNumber(uint16_t iFile);

public:
  SoundPlayer();
  ~SoundPlayer();

  void setup();
  void play(uint16_t iSound, uint8_t iVolume, uint32_t iRepeats = 0, uint32_t iDuration = 0);
  void stop(bool force = false);
  void loop();
  void setVolume(uint8_t iVolume);

  void powerOn();
  void powerOff();
};