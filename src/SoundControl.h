#pragma once
#include "SoundPlayer.h"
#include "SoundTrigger.h"
#include "Helper.h"
#include "KnxHelper.h"

#define SOM_SceneActionStart 1
#define SOM_SceneActionStop 2
#define SOM_SceneActionLock 3
#define SOM_SceneActionUnlock 4

class SoundControl
{

public:
  SoundControl();
  ~SoundControl();

  bool play(uint8_t file, uint8_t volume, uint8_t priority, bool repeat);
  bool play(uint8_t file, uint8_t volume, uint8_t priority, bool repeat, uint8_t trigger);
  void stop();
  void loop();
  void setup();
  void stopped();
  void lock();
  void unlock();
  void day();
  void night();
  void processInputKo(GroupObject &ko);
  static SoundControl *instance;

private:
  void processInputKoLock(GroupObject &ko);
  void processInputKoDayNight(GroupObject &ko);
  void processInputKoScene(GroupObject &ko);
  void processInputKoExternalVolume(GroupObject &ko);
  void processInputKoExternalPriority(GroupObject &ko);
  void processInputKoExternalFile(GroupObject &ko);
  void setDefaultVolume();
  SoundPlayer player;
  SoundTrigger *triggers[SOM_ChannelCount];
  GroupObject *getKo(uint8_t numberKo);
  bool status = false;
  bool currentNight = false;
  bool currentLocked = false;
  bool paramDayNight = false;
  bool paramExternal = false;
  bool paramLock = false;
  bool paramScenes = false;
  uint8_t paramTriggers = 0;
  uint8_t paramVolumeDay = 0;
  uint8_t paramVolumeNight = 0;
  uint8_t currentDefaultVolume = 0;
  uint8_t lastFile = 0;
  uint8_t lastPriority = 0;
  uint8_t lastVolume = 0;
  uint8_t lastTrigger = 0;
  uint8_t externalVolume = 0;
  uint8_t externalPriority = 0;
};