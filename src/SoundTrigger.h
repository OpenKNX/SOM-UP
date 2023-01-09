#pragma once
#include "knx.h"
#include "OpenKNX/Module.h"

class SoundControl;
class SoundTrigger : public OpenKNX::Module
{
private:
  // uint32_t calcParamIndex(uint16_t iParamIndex);
  // uint16_t calcKoNumber(uint8_t iKoIndex);
  // int8_t calcKoIndex(uint16_t iKoNumber);
  // GroupObject *getKo(uint8_t iKoIndex);

  void processInputKoTrigger(GroupObject &iKo);
  void processInputKoLock(GroupObject &iKo);
  void processInputKoDayNight(GroupObject &iKo);

  uint8_t mIndex = 0;
  uint16_t mCurrentFile = 0;
  uint8_t mCurrentVolume = 0;
  uint8_t mParamPriority = 0;
  uint8_t mParamLock = 0;
  uint8_t mParamDayNight = 0;
  uint8_t mParamVolumeDay = 0;
  uint8_t mParamVolumeNight = 0;
  uint16_t mParamFileDay = 0;
  uint16_t mParamFileNight = 0;
  uint32_t mParamDuration = 0;
  uint32_t mParamRepeats = 0;

  bool mParamActive = false;
  bool mCurrentLocked = false;
  bool mStatus = false;

public:
  SoundTrigger(uint8_t iIndex);
  ~SoundTrigger();

  void processInputKo(GroupObject &iKo);
  void setup();
  void loop();
  void lock();
  void unlock();
  void day();
  void night();
  void play();
  void stop();
  void stopped();
  void setStatus(bool iValue);
};