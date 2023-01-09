#pragma once
#include "SoundPlayer.h"
#include "SoundTrigger.h"
#include "Helper.h"
#include "KnxHelper.h"

#define SOM_SceneActionStart 1
#define SOM_SceneActionStop 2
#define SOM_SceneActionLock 3
#define SOM_SceneActionUnlock 4

class SoundControl : public OpenKNX::Module
{

public:
  SoundControl();
  ~SoundControl();

  bool play(uint8_t iFile, uint8_t iVolume = 0, uint8_t IPriority = 3, uint32_t iRepeats = 0, uint32_t iDuration = 0, uint8_t iTrigger = 0);
  void stop();
  void loop();
  void setup();
  void stopped();
  void lock();
  void unlock();
  void day();
  void night();
  void processInputKo(GroupObject &iKo);
  static SoundControl *sInstance;

private:
  void processInputKoLock(GroupObject &iKo);
  void processInputKoDayNight(GroupObject &iKo);
  void processInputKoScene(GroupObject &iKo);
  void processInputKoExternalVolume(GroupObject &iKo);
  void processInputKoExternalPriority(GroupObject &iKo);
  void processInputKoExternalFile(GroupObject &iKo);
  void setDefaultVolume();
  void onSafePinInterruptHandler();
  SoundPlayer mPlayer;
  SoundTrigger *mTriggers[SOM_ChannelCount];
  //GroupObject *getKo(uint8_t iNumberKo);
  bool mStatus = false;
  bool mCurrentNight = false;
  bool mCurrentLocked = false;
  bool mParamDayNight = false;
  bool mParamExternal = false;
  bool mParamLock = false;
  bool mParamScenes = false;
  uint8_t mParamVolumeDay = 0;
  uint8_t mParamVolumeNight = 0;
  uint8_t mCurrentDefaultVolume = 0;
  uint8_t mLastFile = 0;
  uint8_t mLastPriority = 0;
  uint8_t mLastVolume = 0;
  uint8_t mLastTrigger = 0;
  uint8_t mExternalVolume = 0;
  uint8_t mExternalPriority = 0;
};