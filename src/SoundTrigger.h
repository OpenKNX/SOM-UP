#pragma once
#include "OpenKNX.h"

class SoundTrigger : public OpenKNX::Channel
{
private:

  void processInputKoTrigger(GroupObject &ko);
  void processInputKoLock(GroupObject &ko);
  void processInputKoDayNight(GroupObject &ko);

  uint8_t _channelIndex = 0;
  uint16_t _currentFile = 0;
  uint8_t _currentVolume = 0;
  uint8_t _paramPriority = 0;
  uint8_t _paramLock = 0;
  uint8_t _paramDayNight = 0;
  uint8_t _paramVolumeDay = 0;
  uint8_t _paramVolumeNight = 0;
  uint16_t _paramFileDay = 0;
  uint16_t _paramFileNight = 0;
  uint32_t _paramDuration = 0;
  uint32_t _paramRepeats = 0;

  bool _paramActive = false;
  bool _currentLocked = false;
  bool _status = false;

public:
  SoundTrigger(uint8_t index);
  const char* name() override;

  void processInputKo(GroupObject &ko);
  void setup();
  void lock();
  void unlock();
  void day();
  void night();
  void play();
  void stop();
  void stopped();
  void setStatus(bool value);
};