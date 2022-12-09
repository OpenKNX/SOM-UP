#include "SoundControl.h"

SoundControl *SoundControl::instance = nullptr;

SoundControl::SoundControl()
{
  SoundControl::instance = this;
}
SoundControl::~SoundControl() {}

GroupObject *SoundControl::getKo(uint8_t numberKo)
{
  return &knx.getGroupObject(numberKo);
}

void SoundControl::setup()
{
  // Params
  paramTriggers = knx.paramByte(SOM_NumTriggers); // TODO
  paramTriggers = 10;
  paramScenes = (knx.paramByte(SOM_Scenes) & SOM_ScenesMask) >> SOM_ScenesShift;
  paramExternal = (knx.paramByte(SOM_External) & SOM_ExternalMask) >> SOM_ExternalShift;
  paramLock = (knx.paramByte(SOM_Lock) & SOM_LockMask) >> SOM_LockShift;
  paramDayNight = (knx.paramByte(SOM_DayNight) & SOM_DayNightMask) >> SOM_DayNightShift;
  paramVolumeDay = knx.paramByte(SOM_VolumeDay);
  paramVolumeNight = knx.paramByte(SOM_VolumeNight);
  currentDefaultVolume = paramVolumeDay;

  // Default
  getKo(SOM_KoStatus)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoLock)->valueNoSend(false, getDPT(VAL_DPT_1));

  // Debug
  SERIAL_DEBUG.printf("paramVolumeDay %i\n\r", paramVolumeDay);
  SERIAL_DEBUG.printf("paramVolumeNight %i\n\r", paramVolumeNight);
  SERIAL_DEBUG.printf("paramExternal %i\n\r", paramExternal);
  SERIAL_DEBUG.printf("paramScenes %i\n\r", paramScenes);
  SERIAL_DEBUG.printf("paramDayNight %i\n\r", paramDayNight);
  SERIAL_DEBUG.printf("paramLock %i\n\r", paramLock);
  SERIAL_DEBUG.printf("paramTriggers %i\n\r", paramTriggers);

  // Call dependend setup
  player.setup();
  for (uint8_t i = 0; i < paramTriggers; i++)
  {
    triggers[i] = new SoundTrigger(i);
    triggers[i]->setup();
  }
}

bool SoundControl::play(uint8_t file, uint8_t volume, uint8_t priority, bool repeat)
{
  return SoundControl::play(file, volume, priority, repeat, 0);
}

bool SoundControl::play(uint8_t file, uint8_t volume, uint8_t priority, bool repeat, uint8_t trigger)
{
  SERIAL_DEBUG.printf("SoundControl::play %i/%i/%i/%i/%i\n\r", file, volume, priority, repeat, trigger);

  // abort on lock
  if (currentLocked)
  {
    SERIAL_DEBUG.printf("SoundControl::play ignore -> lock\n\r");
    return false;
  }

  // skip if higher prio while playing
  if (status && lastPriority > priority)
  {
    SERIAL_DEBUG.printf("SoundControl::play ignore -> prio\n\r");
    return false;
  }

  // use default volume if zero
  if (volume == 0)
    volume = currentDefaultVolume;

  // reset states
  SoundControl::stopped();

  // play music
  player.play(file, volume, repeat);

  // send ko
  getKo(SOM_KoStatus)->value(true, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->value(file, getDPT(VAL_DPT_5));

  // save status
  status = true;
  lastFile = file;
  lastVolume = volume;
  lastPriority = priority;
  lastTrigger = trigger;

  return true;
}
void SoundControl::stop()
{
  SERIAL_DEBUG.println("SoundControl::stop");
  player.stop();
}
void SoundControl::stopped()
{
  SERIAL_DEBUG.println("SoundControl::stopped");
  for (uint8_t i = 0; i < paramTriggers; i++)
  {
    SoundTrigger *trigger = triggers[i];
    trigger->stopped();
  }
  status = false;
  getKo(SOM_KoStatus)->value(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->value((uint8_t)0, getDPT(VAL_DPT_5));
}

void SoundControl::loop()
{
  if (!knx.configured())
    return;

  player.loop();
  for (uint8_t i = 0; i < paramTriggers; i++)
  {
    triggers[i]->loop();
  }
}

void SoundControl::lock()
{
  if (paramLock == 0 || currentLocked)
    return;

  currentLocked = true;
  stop();
  getKo(SOM_KoLock)->value(currentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.println("Lock Global");
}

void SoundControl::unlock()
{
  if (paramLock == 0 || !currentLocked)
    return;

  currentLocked = false;
  getKo(SOM_KoLock)->value(currentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.println("Unlocked Gobal");
}

void SoundControl::day()
{
  SERIAL_DEBUG.printf("Switch to day\n\r");
  currentNight = false;
  setDefaultVolume();
}
void SoundControl::night()
{
  SERIAL_DEBUG.printf("Switch to night\n\r");
  currentNight = true;
  setDefaultVolume();
}

void SoundControl::processInputKo(GroupObject &ko)
{
  // we have to check first, if external KO are used
  uint16_t asap = ko.asap();
  switch (asap)
  {
  case SOM_KoDayNight:
    processInputKoDayNight(ko);
    break;

  case SOM_KoLock:
    processInputKoLock(ko);
    break;

  case SOM_KoScene:
    processInputKoScene(ko);
    break;

  case SOM_KoExternalFile:
    processInputKoExternalFile(ko);
    break;

  case SOM_KoExternalVolume:
    processInputKoExternalVolume(ko);
    break;

  case SOM_KoExternalPriority:
    processInputKoExternalPriority(ko);
    break;

  default:
    // forward to trigger
    if (asap >= SOM_KoOffset && asap < SOM_KoOffset + paramTriggers * SOM_KoBlockSize)
    {
      uint8_t index = (asap - SOM_KoOffset) / SOM_KoBlockSize;
      triggers[index]->processInputKo(ko);
    }
    break;
  }
}

void SoundControl::processInputKoLock(GroupObject &ko)
{
  bool value = ko.value(getDPT(VAL_DPT_1));

  if (paramLock == 1 && value == 1 || paramLock == 2 && value == 0)
    return lock();

  return unlock();
}
void SoundControl::processInputKoDayNight(GroupObject &ko)
{
  bool value = ko.value(getDPT(VAL_DPT_1));

  if (paramDayNight == 1 && value == 0 || paramDayNight == 2 && value == 1)
    return night();

  return day();
}

void SoundControl::processInputKoScene(GroupObject &ko)
{
  uint8_t value = ko.value(getDPT(VAL_DPT_17));

  value += 1;
  if (value > 0 && value <= 64)
  {

    for (uint8_t i = 0; i < 20; i++)
    {
      uint8_t sceneId = knx.paramByte(SOM_Scene0 + i);
      if (value == sceneId)
      {
        SERIAL_DEBUG.printf("Szene %i\n\r", value);
        uint8_t sceneAction = knx.paramByte(SOM_SceneAction0 + i);
        uint8_t sceneTarget = knx.paramByte(SOM_SceneTargetA0 + i);
  
        // Zentral
        if (sceneTarget == 255)
        {
          switch (sceneAction)
          {
          case SOM_SceneActionStop:
            this->stop();
            break;
          case SOM_SceneActionLock:
            this->lock();
            break;
          case SOM_SceneActionUnlock:
            this->unlock();
            break;
          default:
            break;
          }
        }
        else
        {
          SoundTrigger *trigger = triggers[sceneTarget];
          switch (sceneAction)
          {
          case SOM_SceneActionStart:
            trigger->play();
            break;
          case SOM_SceneActionStop:
            trigger->stop();
            break;
          case SOM_SceneActionLock:
            trigger->lock();
            break;
          case SOM_SceneActionUnlock:
            trigger->unlock();
            break;
          default:
            break;
          }
        }
      }
    }
  }
}

void SoundControl::processInputKoExternalVolume(GroupObject &ko)
{
  uint8_t value = ko.value(getDPT(VAL_DPT_5));
  
  // invalid volume
  if (value < 0 || value > 30)
    value = 0;

  externalVolume = value;
}

void SoundControl::processInputKoExternalPriority(GroupObject &ko)
{
  uint8_t value = ko.value(getDPT(VAL_DPT_5));
  
  // invalid volume
  if (value < 1 || value > 5)
    value = 3;

  externalPriority = value;
}

void SoundControl::processInputKoExternalFile(GroupObject &ko)
{
  uint8_t file = ko.value(getDPT(VAL_DPT_5));
  
  if(file == 0)
    return stop();

  // invalid volume
  if (file < 1 || file > 255)
    return;

  play(file, externalVolume, externalPriority, false);
}

void SoundControl::setDefaultVolume() {
  // Dont set during playing
  if (status)
    return;

  // select currentDefaultVolume
  if (currentNight) {
    currentDefaultVolume = paramVolumeNight;
  } else {
    currentDefaultVolume = paramVolumeDay;
  }

  // update currentDefaultVolume
  player.setVolume(currentDefaultVolume);
}