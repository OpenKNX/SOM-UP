#pragma once
#include "knx.h"

class SoundControl;
class SoundTrigger
{
private:
  uint32_t calcParamIndex(uint16_t paramIndex);
  uint16_t calcKoNumber(uint8_t koIndex);
  int8_t calcKoIndex(uint16_t koNumber);
  GroupObject *getKo(uint8_t koIndex);

  void processInputKoTrigger(GroupObject &ko);
  void processInputKoLock(GroupObject &ko);
  void processInputKoDayNight(GroupObject &ko);
  void processDuration();

  uint8_t index = 0;
  uint8_t currentFile;
  uint8_t currentVolume;
  uint8_t paramPriority;
  uint8_t paramLock;
  uint8_t paramDayNight;
  uint8_t paramVolumeDay;
  uint8_t paramVolumeNight;
  uint8_t paramFileDay;
  uint8_t paramFileNight;
  uint32_t paramDuration;
  
  bool paramActive = false;
  bool paramRepeat = false;
  bool currentLocked = false;
  bool status = false;
  uint32_t startMillis = 0;

public:
  SoundTrigger(uint8_t index);
  ~SoundTrigger();

  void processInputKo(GroupObject &ko);
  void setup();
  void loop();
  void lock();
  void unlock();
  void day();
  void night();
  void play();
  void stop();
  void stopped();
  void setStatus(bool value);
};