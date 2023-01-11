#include "SoundControl.h"
#include "SoundTrigger.h"

SoundTrigger::SoundTrigger(uint8_t iIndex)
{
  mIndex = iIndex;
  mChannelIndex = mIndex;
  mChannelParamBlockSize = SOM_ParamBlockSize;
  mChannelParamOffset = SOM_ParamBlockOffset;
  mChannelParamKoBlockSize = SOM_KoBlockSize;
  mChannelParamKoOffset = SOM_KoOffset;
}

SoundTrigger::~SoundTrigger() {}

void SoundTrigger::setup()
{
  // Params
  mParamActive = (knx.paramByte(calcParamIndex(SOM_TriggerState)) & SOM_TriggerStateMask) >> SOM_TriggerStateShift;
  mParamRepeats = (knx.paramWord(calcParamIndex(SOM_TriggerRepeats)));
  mParamPriority = (knx.paramByte(calcParamIndex(SOM_TriggerPriority)) & SOM_TriggerPriorityMask) >> SOM_TriggerPriorityShift;
  mParamLock = (knx.paramByte(calcParamIndex(SOM_TriggerLock)) & SOM_TriggerLockMask) >> SOM_TriggerLockShift;
  mParamDayNight = (knx.paramByte(calcParamIndex(SOM_TriggerDayNight)) & SOM_TriggerDayNightMask) >> SOM_TriggerDayNightShift;
  mParamVolumeDay = (knx.paramByte(calcParamIndex(SOM_TriggerVolumeDay)));
  mParamVolumeNight = (knx.paramByte(calcParamIndex(SOM_TriggerVolumeNight)));
  mParamFileDay = (knx.paramWord(calcParamIndex(SOM_TriggerFileDay)));
  mParamFileNight = (knx.paramWord(calcParamIndex(SOM_TriggerFileNight)));
  mParamDuration = (getDelayPattern(calcParamIndex(SOM_TriggerDurationBase)));

  // Default
  mCurrentVolume = mParamVolumeDay;
  mCurrentFile = mParamFileDay;
  getKo(SOM_KoTriggerStatus)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoTriggerLock)->valueNoSend(false, getDPT(VAL_DPT_1));

  // Debug
  SERIAL_DEBUG.printf("Trigger %i mParamActive: %i\n\r", mIndex, mParamActive);
  SERIAL_DEBUG.printf("Trigger %i mParamRepeats: %i\n\r", mIndex, mParamRepeats);
  SERIAL_DEBUG.printf("Trigger %i mParamPriority: %i\n\r", mIndex, mParamPriority);
  SERIAL_DEBUG.printf("Trigger %i mParamLock: %i\n\r", mIndex, mParamLock);
  SERIAL_DEBUG.printf("Trigger %i mParamDayNight: %i\n\r", mIndex, mParamDayNight);
  SERIAL_DEBUG.printf("Trigger %i mParamVolumeDay: %i\n\r", mIndex, mParamVolumeDay);
  SERIAL_DEBUG.printf("Trigger %i mParamVolumeNight: %i\n\r", mIndex, mParamVolumeNight);
  SERIAL_DEBUG.printf("Trigger %i mParamFileDay: %i\n\r", mIndex, mParamFileDay);
  SERIAL_DEBUG.printf("Trigger %i mParamFileNight: %i\n\r", mIndex, mParamFileNight);
  SERIAL_DEBUG.printf("Trigger %i mParamDuration: %i\n\r", mIndex, mParamDuration);
}

/*uint32_t SoundTrigger::calcParamIndex(uint16_t iParamIndex)
{
  return iParamIndex + mIndex * SOM_ParamBlockSize + SOM_ParamBlockOffset;
}

uint16_t SoundTrigger::calcKoNumber(uint8_t iKoIndex)
{
  return iKoIndex + mIndex * SOM_KoBlockSize + SOM_KoOffset;
}

int8_t SoundTrigger::calcKoIndex(uint16_t iKoNumber)
{
  int16_t lResult = (iKoNumber - SOM_KoOffset);
  // check if channel is valid
  if ((int8_t)(lResult / SOM_KoBlockSize) == mIndex)
    lResult = lResult % SOM_KoBlockSize;
  else
    lResult = -1;
  return (int8_t)lResult;
}

GroupObject *SoundTrigger::getKo(uint8_t iKoIndex)
{
  return &knx.getGroupObject(calcKoNumber(iKoIndex));
}
*/
void SoundTrigger::loop()
{
};

void SoundTrigger::processInputKo(GroupObject &iKo)
{
  if (!mParamActive)
    return;

  switch (calcKoIndex(iKo.asap()))
  {
  case SOM_KoTriggerTrigger:
    processInputKoTrigger(iKo);
    break;
  case SOM_KoTriggerLock:
    processInputKoLock(iKo);
    break;
  case SOM_KoTriggerDayNight:
    processInputKoDayNight(iKo);
    break;
  }
}

void SoundTrigger::processInputKoTrigger(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));

  if (lValue)
    return play();

  return stop();
}

void SoundTrigger::processInputKoDayNight(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));

  if (mParamDayNight == 1 && lValue == 0 || mParamDayNight == 2 && lValue == 1)
    return night();

  return day();
}

void SoundTrigger::processInputKoLock(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));

  if (mParamLock == 1 && lValue == 1 || mParamLock == 2 && lValue == 0)
    return lock();

  return unlock();
}

void SoundTrigger::lock()
{
  if (mParamLock == 0 || mCurrentLocked)
    return;

  mCurrentLocked = true;
  stop();
  getKo(SOM_KoTriggerLock)->value(mCurrentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.printf("Lock Trigger %i\n\r", mIndex);
}

void SoundTrigger::unlock()
{
  if (mParamLock == 0 || !mCurrentLocked)
    return;

  mCurrentLocked = false;
  getKo(SOM_KoTriggerLock)->value(mCurrentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.printf("Unlock Trigger %i\n\r", mIndex);
}

void SoundTrigger::day()
{
  SERIAL_DEBUG.printf("Trigger %i switch to day\n\r", mIndex);
  mCurrentVolume = mParamVolumeDay;
  mCurrentFile = mParamFileDay;
}

void SoundTrigger::night()
{
  SERIAL_DEBUG.printf("Trigger %i switch to night\n\r", mIndex);
  mCurrentVolume = mParamVolumeNight;
  mCurrentFile = mParamFileNight;
}

void SoundTrigger::play()
{
  if (mCurrentLocked)
  {
    SERIAL_DEBUG.printf("Trigger %i play ignored (locked)\n\r", mIndex);
    return;
  }
  SERIAL_DEBUG.printf("Trigger %i play\n\r", mIndex);
  setStatus(SoundControl::sInstance->play(mCurrentFile, mCurrentVolume, mParamPriority, mParamRepeats, mParamDuration, mIndex));
}

void SoundTrigger::stop()
{
  // skip if not playing
  if (!mStatus)
    return;

  SERIAL_DEBUG.printf("Trigger %i stop\n\r", mIndex);
  setStatus(false);
  SoundControl::sInstance->stop();
}

void SoundTrigger::stopped()
{
  setStatus(false);
}

void SoundTrigger::setStatus(bool iNewStatus)
{
  if (mStatus != iNewStatus)
  {
    mStatus = iNewStatus;
    getKo(SOM_KoTriggerStatus)->value(mStatus, getDPT(VAL_DPT_1));
  }
}
