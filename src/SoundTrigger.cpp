#include "SoundControl.h"
#include "SoundTrigger.h"

SoundTrigger::SoundTrigger(uint8_t index)
{
  this->index = index;
}

SoundTrigger::~SoundTrigger() {}

void SoundTrigger::setup()
{
  // Params
  paramActive = (knx.paramByte(calcParamIndex(SOM_TriState)) & SOM_TriStateMask) >> SOM_TriStateShift;
  paramRepeat = (knx.paramByte(calcParamIndex(SOM_TriRepeat)) & SOM_TriRepeatMask) >> SOM_TriRepeatShift;
  paramPriority = (knx.paramByte(calcParamIndex(SOM_TriPriority)) & SOM_TriPriorityMask) >> SOM_TriPriorityShift;
  paramLock = (knx.paramByte(calcParamIndex(SOM_TriLock)) & SOM_TriLockMask) >> SOM_TriLockShift;
  paramDayNight = (knx.paramByte(calcParamIndex(SOM_TriDayNight)) & SOM_TriDayNightMask) >> SOM_TriDayNightShift;
  paramVolumeDay = (knx.paramByte(calcParamIndex(SOM_TriVolumeDay)));
  paramVolumeNight = (knx.paramByte(calcParamIndex(SOM_TriVolumeNight)));
  paramFileDay = (knx.paramByte(calcParamIndex(SOM_TriFileDay)));
  paramFileNight = (knx.paramByte(calcParamIndex(SOM_TriFileNight)));
  paramDuration = (getDelayPattern(calcParamIndex(SOM_TriDurationBase)));

  // Default
  currentVolume = paramVolumeDay;
  currentFile = paramFileDay;
  getKo(SOM_KoTriStatus)->valueNoSend(false, getDPT(VAL_DPT_1));
  getKo(SOM_KoTriLock)->valueNoSend(false, getDPT(VAL_DPT_1));

  // Debug
  SERIAL_DEBUG.printf("Trigger %i paramActive: %i\n\r", index, paramActive);
  SERIAL_DEBUG.printf("Trigger %i paramRepeat: %i\n\r", index, paramRepeat);
  SERIAL_DEBUG.printf("Trigger %i paramPriority: %i\n\r", index, paramPriority);
  SERIAL_DEBUG.printf("Trigger %i paramLock: %i\n\r", index, paramLock);
  SERIAL_DEBUG.printf("Trigger %i paramDayNight: %i\n\r", index, paramDayNight);
  SERIAL_DEBUG.printf("Trigger %i paramVolumeDay: %i\n\r", index, paramVolumeDay);
  SERIAL_DEBUG.printf("Trigger %i paramVolumeNight: %i\n\r", index, paramVolumeNight);
  SERIAL_DEBUG.printf("Trigger %i paramFileDay: %i\n\r", index, paramFileDay);
  SERIAL_DEBUG.printf("Trigger %i paramFileNight: %i\n\r", index, paramFileNight);
  SERIAL_DEBUG.printf("Trigger %i paramDuration: %i\n\r", index, paramDuration);
}

uint32_t SoundTrigger::calcParamIndex(uint16_t paramIndex)
{
  return paramIndex + index * SOM_ParamBlockSize + SOM_ParamBlockOffset;
}

uint16_t SoundTrigger::calcKoNumber(uint8_t koIndex)
{
  return koIndex + index * SOM_KoBlockSize + SOM_KoOffset;
}

int8_t SoundTrigger::calcKoIndex(uint16_t koNumber)
{
  int16_t result = (koNumber - SOM_KoOffset);
  // check if channel is valid
  if ((int8_t)(result / SOM_KoBlockSize) == index)
    result = result % SOM_KoBlockSize;
  else
    result = -1;
  return (int8_t)result;
}

GroupObject *SoundTrigger::getKo(uint8_t koIndex)
{
  return &knx.getGroupObject(calcKoNumber(koIndex));
}

void SoundTrigger::loop() {
  processDuration();
};

void SoundTrigger::processDuration() {
  // skip if timer not started?
  if (startMillis == 0)
    return;

  // skip if not playing
  if (!status)
    return;

  // skip if repeated is inactive
  if (!paramRepeat)
    return;

  // timer 
  if ((millis() - startMillis) > paramDuration)
    stop();
};

void SoundTrigger::processInputKo(GroupObject &ko)
{
  // we process KO only if we are running
  if (paramActive)
  {
    switch (calcKoIndex(ko.asap()))
    {
    case SOM_KoTriTrigger:
      processInputKoTrigger(ko);
      break;
    case SOM_KoTriLock:
      processInputKoLock(ko);
      break;
    case SOM_KoTriDayNight:
      processInputKoDayNight(ko);
      break;

    default:
      break;
    }
  }
}

void SoundTrigger::processInputKoTrigger(GroupObject &ko)
{
  bool value = ko.value(getDPT(VAL_DPT_1));

  if (value)
    return play();

  return stop();
}

void SoundTrigger::processInputKoDayNight(GroupObject &ko)
{
  bool value = ko.value(getDPT(VAL_DPT_1));

  if (paramDayNight == 1 && value == 0 || paramDayNight == 2 && value == 1)
    return night();

  return day();
}

void SoundTrigger::processInputKoLock(GroupObject &ko)
{
  bool value = ko.value(getDPT(VAL_DPT_1));

  if (paramLock == 1 && value == 1 || paramLock == 2 && value == 0)
    return lock();

  return unlock();
}

void SoundTrigger::lock()
{
  if (paramLock == 0 || currentLocked)
    return;

  currentLocked = true;
  stop();
  getKo(SOM_KoTriLock)->value(currentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.printf("Lock Trigger %i\n\r", index);
}

void SoundTrigger::unlock()
{
  if (paramLock == 0 || !currentLocked)
    return;

  currentLocked = false;
  getKo(SOM_KoTriLock)->value(currentLocked, getDPT(VAL_DPT_1));
  SERIAL_DEBUG.printf("Unlock Trigger %i\n\r", index);
}

void SoundTrigger::day()
{
  SERIAL_DEBUG.printf("Trigger %i switch to day\n\r", index);
  currentVolume = paramVolumeDay;
  currentFile = paramFileDay;
}

void SoundTrigger::night()
{
  SERIAL_DEBUG.printf("Trigger %i switch to night\n\r", index);
  currentVolume = paramVolumeNight;
  currentFile = paramFileNight;
}

void SoundTrigger::play()
{
  if (currentLocked)
  {
    SERIAL_DEBUG.printf("Trigger %i play ignored (locked)\n\r", index);
    return;
  }
  SERIAL_DEBUG.printf("Trigger %i play\n\r", index);
  setStatus(SoundControl::instance->play(currentFile, currentVolume, paramPriority, paramRepeat, index));
}

void SoundTrigger::stop()
{
  // skip if not playing
  if (!status)
    return;

  SERIAL_DEBUG.printf("Trigger %i stop\n\r", index);
  setStatus(false);
  SoundControl::instance->stop();
}

void SoundTrigger::stopped()
{
  setStatus(false);
}

void SoundTrigger::setStatus(bool newStatus)
{
  // internal timer for max duration
  startMillis = newStatus ? millis() : 0;

  if (status != newStatus) {
    status = newStatus;
    getKo(SOM_KoTriStatus)->value(status, getDPT(VAL_DPT_1));
  }
}
