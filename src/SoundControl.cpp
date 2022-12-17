#include "SoundControl.h"

SoundControl *SoundControl::sInstance = nullptr;

SoundControl::SoundControl()
{
  SoundControl::sInstance = this;
}
SoundControl::~SoundControl() {}

GroupObject *SoundControl::getKo(uint8_t numberKo)
{
  return &knx.getGroupObject(numberKo);
}

void SoundControl::setup()
{
  // Params
  mParamScenes = (knx.paramByte(SOM_Scenes) & SOM_ScenesMask) >> SOM_ScenesShift;
  mParamExternal = (knx.paramByte(SOM_External) & SOM_ExternalMask) >> SOM_ExternalShift;
  mParamLock = (knx.paramByte(SOM_Lock) & SOM_LockMask) >> SOM_LockShift;
  mParamDayNight = (knx.paramByte(SOM_DayNight) & SOM_DayNightMask) >> SOM_DayNightShift;
  mParamVolumeDay = knx.paramByte(SOM_VolumeDay);
  mParamVolumeNight = knx.paramByte(SOM_VolumeNight);
  mCurrentDefaultVolume = mParamVolumeDay;

  // Default
  getKo(SOM_KoStatus)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoLock)->valueNoSend(false, getDPT(VAL_DPT_1));

  // Debug
  SERIAL_DEBUG.printf("mParamVolumeDay %i\n\r", mParamVolumeDay);
  SERIAL_DEBUG.printf("mParamVolumeNight %i\n\r", mParamVolumeNight);
  SERIAL_DEBUG.printf("mParamExternal %i\n\r", mParamExternal);
  SERIAL_DEBUG.printf("mParamScenes %i\n\r", mParamScenes);
  SERIAL_DEBUG.printf("mParamDayNight %i\n\r", mParamDayNight);
  SERIAL_DEBUG.printf("mParamLock %i\n\r", mParamLock);

  // Call dependend setup
  mPlayer.setup();
  for (uint8_t i = 0; i < SOM_ChannelCount; i++)
  {
    mTriggers[i] = new SoundTrigger(i);
    mTriggers[i]->setup();
  }
}

bool SoundControl::play(uint8_t iFile, uint8_t iVolume, uint8_t iPriority, bool iRepeat, uint8_t iTrigger)
{
  SERIAL_DEBUG.printf("SoundControl::play %i/%i/%i/%i/%i\n\r", iFile, iVolume, iPriority, iRepeat, iTrigger);

  // abort on lock
  if (mCurrentLocked)
  {
    SERIAL_DEBUG.printf("SoundControl::play ignore -> lock\n\r");
    return false;
  }

  // skip if higher prio while playing
  if (mStatus && mLastPriority > iPriority)
  {
    SERIAL_DEBUG.printf("SoundControl::play ignore -> prio\n\r");
    return false;
  }

  // use default volume if zero
  if (iVolume == 0)
    iVolume = mCurrentDefaultVolume;

  // reset states
  SoundControl::stopped();

  // play music
  mPlayer.play(iFile, iVolume, iRepeat);

  // send ko
  getKo(SOM_KoStatus)->value(true, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->value(iFile, getDPT(VAL_DPT_5));

  // save status
  mStatus = true;
  mLastFile = iFile;
  mLastVolume = iVolume;
  mLastPriority = iPriority;
  mLastTrigger = iTrigger;

  return true;
}
void SoundControl::stop()
{
  SERIAL_DEBUG.println("SoundControl::stop");
  mPlayer.stop();
}
void SoundControl::stopped()
{
  SERIAL_DEBUG.println("SoundControl::stopped");
  for (uint8_t i = 0; i < SOM_ChannelCount; i++)
  {
    SoundTrigger *lTrigger = mTriggers[i];
    lTrigger->stopped();
  }
  mStatus = false;
  getKo(SOM_KoStatus)->value(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoFile)->value((uint8_t)0, getDPT(VAL_DPT_5));
}

void SoundControl::loop()
{
  if (!knx.configured())
    return;

  mPlayer.loop();
  for (uint8_t i = 0; i < SOM_ChannelCount; i++)
  {
    mTriggers[i]->loop();
  }
}

void SoundControl::lock()
{
  if (mParamLock == 0 || mCurrentLocked)
    return;

  mCurrentLocked = true;
  stop();
  getKo(SOM_KoLock)->value(mCurrentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.println("Lock Global");
}

void SoundControl::unlock()
{
  if (mParamLock == 0 || !mCurrentLocked)
    return;

  mCurrentLocked = false;
  getKo(SOM_KoLock)->value(mCurrentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.println("Unlocked Gobal");
}

void SoundControl::day()
{
  SERIAL_DEBUG.printf("Switch to day\n\r");
  mCurrentNight = false;
  setDefaultVolume();
}
void SoundControl::night()
{
  SERIAL_DEBUG.printf("Switch to night\n\r");
  mCurrentNight = true;
  setDefaultVolume();
}

void SoundControl::processInputKo(GroupObject &iKo)
{
  // we have to check first, if external KO are used
  uint16_t lAsap = iKo.asap();
  switch (lAsap)
  {
  case SOM_KoDayNight:
    processInputKoDayNight(iKo);
    break;

  case SOM_KoLock:
    processInputKoLock(iKo);
    break;

  case SOM_KoScene:
    processInputKoScene(iKo);
    break;

  case SOM_KoExternalFile:
    processInputKoExternalFile(iKo);
    break;

  case SOM_KoExternalVolume:
    processInputKoExternalVolume(iKo);
    break;

  case SOM_KoExternalPriority:
    processInputKoExternalPriority(iKo);
    break;

  default:
    // forward to trigger
    if (lAsap >= SOM_KoOffset && lAsap < SOM_KoOffset + SOM_ChannelCount * SOM_KoBlockSize)
    {
      uint8_t lIndex = (lAsap - SOM_KoOffset) / SOM_KoBlockSize;
      mTriggers[lIndex]->processInputKo(iKo);
    }
    break;
  }
}

void SoundControl::processInputKoLock(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));

  if (mParamLock == 1 && lValue == 1 || mParamLock == 2 && lValue == 0)
    return lock();

  return unlock();
}
void SoundControl::processInputKoDayNight(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));

  if (mParamDayNight == 1 && lValue == 0 || mParamDayNight == 2 && lValue == 1)
    return night();

  return day();
}

void SoundControl::processInputKoScene(GroupObject &iKo)
{
  uint8_t lValue = iKo.value(getDPT(VAL_DPT_17));

  lValue += 1;
  if (lValue > 0 && lValue <= 64)
  {

    for (uint8_t i = 0; i < 20; i++)
    {
      uint8_t sceneId = knx.paramByte(SOM_Scene0 + i);
      if (lValue == sceneId)
      {
        SERIAL_DEBUG.printf("Szene %i\n\r", lValue);
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
          SoundTrigger *trigger = mTriggers[sceneTarget];
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

void SoundControl::processInputKoExternalVolume(GroupObject &iKo)
{
  uint8_t lValue = iKo.value(getDPT(VAL_DPT_5));
  
  // invalid volume
  if (lValue < 0 || lValue > 30)
    lValue = 0;

  mExternalVolume = lValue;
}

void SoundControl::processInputKoExternalPriority(GroupObject &iKo)
{
  uint8_t lValue = iKo.value(getDPT(VAL_DPT_5));
  
  // invalid volume
  if (lValue < 1 || lValue > 5)
    lValue = 3;

  mExternalPriority = lValue;
}

void SoundControl::processInputKoExternalFile(GroupObject &iKo)
{
  uint8_t iFile = iKo.value(getDPT(VAL_DPT_5));
  
  if(iFile == 0)
    return stop();

  // invalid volume
  if (iFile < 1 || iFile > 255)
    return;

  play(iFile, mExternalVolume, mExternalPriority, false);
}

void SoundControl::setDefaultVolume() {
  // Dont set during playing
  if (mStatus)
    return;

  // select mCurrentDefaultVolume
  if (mCurrentNight) {
    mCurrentDefaultVolume = mParamVolumeNight;
  } else {
    mCurrentDefaultVolume = mParamVolumeDay;
  }

  // update mCurrentDefaultVolume
  mPlayer.setVolume(mCurrentDefaultVolume);
}