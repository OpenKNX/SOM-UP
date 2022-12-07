#pragma once
#include "DYPlayerArduino.h"
#include "SoundModul.h"
// #include "hardware.h"
#include "SoundModulHardware.h"
#include <iomanip>
#include <iostream>

class SoundControl;

class SoundPlayer
{
  
private:
  DY::Player hardware;
  bool status = false;
  void processStatus();
  void requestStatus();
  unsigned long previousMillis = 0;
  bool waitForPlaying = false;
  uint8_t lastVolume = 0;
  DY::play_state_t lastState = DY::PlayState::Stopped;
  bool waitForState = false;
  uint8_t responseStateBuffer[5];
  uint8_t responseStatePos = 0;

public:
  SoundPlayer();
  ~SoundPlayer();

  void setup();
  void play(uint8_t sound, uint8_t volume, bool repeat);
  void stop();
  void loop();
  void setVolume(uint8_t volume);
};