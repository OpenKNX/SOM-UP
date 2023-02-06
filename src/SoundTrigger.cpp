#include "SoundTrigger.h"
#include "SoundModule.h"

SoundTrigger::SoundTrigger(uint8_t index)
{
    _channelIndex = index;
}

const char *SoundTrigger::name()
{
    char *buffer = new char[17];
    sprintf(buffer, "SoundTrigger<%i>", _channelIndex + 1);
    return buffer;
}

void SoundTrigger::setup()
{
    _currentVolume = ParamSOM_TriggerVolumeDay;
    _currentFile = ParamSOM_TriggerFileDay;
    KoSOM_TriggerStatus.valueNoSend(false, DPT_Switch);
    KoSOM_TriggerLock.valueNoSend(false, DPT_Switch);

// Debug
#ifdef DEBUG_SOUND
    log("paramActive: %i", ParamSOM_TriggerState);
    log("paramRepeats: %i", ParamSOM_TriggerRepeats);
    log("paramPriority: %i", ParamSOM_TriggerPriority);
    log("paramLock: %i", ParamSOM_TriggerLock);
    log("paramDayNight: %i", ParamSOM_TriggerDayNight);
    log("paramVolumeDay: %i", ParamSOM_TriggerVolumeDay);
    log("paramVolumeNight: %i", ParamSOM_TriggerVolumeNight);
    log("paramFileDay: %i", ParamSOM_TriggerFileDay);
    log("paramFileNight: %i", ParamSOM_TriggerFileNight);
    log("paramDurationMS: %i", ParamSOM_TriggerDurationTimeMS);
#endif
}

void SoundTrigger::processInputKo(GroupObject &ko)
{
    if (!ParamSOM_TriggerState)
        return;

    switch (SOM_KoCalcIndex(ko.asap()))
    {
        case SOM_KoTriggerTrigger:
            processInputKoTrigger(ko);
            break;
        case SOM_KoTriggerLock:
            processInputKoLock(ko);
            break;
        case SOM_KoTriggerDayNight:
            processInputKoDayNight(ko);
            break;
    }
}

void SoundTrigger::processInputKoTrigger(GroupObject &ko)
{
    if (ko.value(DPT_Switch))
        return play();

    return stop();
}

void SoundTrigger::processInputKoDayNight(GroupObject &ko)
{
    bool value = ko.value(DPT_Switch);

    if (ParamSOM_TriggerDayNight == 1 && value == 0 || ParamSOM_TriggerDayNight == 2 && value == 1)
        return night();

    return day();
}

void SoundTrigger::processInputKoLock(GroupObject &ko)
{
    bool value = ko.value(DPT_Switch);

    if (ParamSOM_TriggerLock == 1 && value == 1 || ParamSOM_TriggerLock == 2 && value == 0)
        return lock();

    return unlock();
}

void SoundTrigger::lock()
{
    if (ParamSOM_TriggerLock == 0 || _currentLocked)
        return;

    _currentLocked = true;
    stop();
    KoSOM_TriggerLock.value(_currentLocked, DPT_Switch);
    log("lock");
}

void SoundTrigger::unlock()
{
    if (ParamSOM_TriggerLock == 0 || !_currentLocked)
        return;

    _currentLocked = false;
    KoSOM_TriggerLock.value(_currentLocked, DPT_Switch);
    log("unlock");
}

void SoundTrigger::day()
{
    log("day mode");
    _currentVolume = ParamSOM_TriggerVolumeDay;
    _currentFile = ParamSOM_TriggerFileDay;
}

void SoundTrigger::night()
{
    log("night mode");
    _currentVolume = ParamSOM_TriggerVolumeNight;
    _currentFile = ParamSOM_TriggerFileNight;
}

void SoundTrigger::play()
{
    if (_currentLocked)
    {
        log("play ignored (locked)");
        return;
    }
    log("play");
    setStatus(SoundModule::instance()->play(_currentFile, _currentVolume, ParamSOM_TriggerPriority, ParamSOM_TriggerRepeats, ParamSOM_TriggerDurationTimeMS, _channelIndex));
}

void SoundTrigger::stop()
{
    // skip if not playing
    if (!_status)
        return;

    log("stop");
    setStatus(false);
    SoundModule::instance()->stop();
}

void SoundTrigger::stopped()
{
    setStatus(false);
}

void SoundTrigger::setStatus(bool newStatus)
{
    if (_status != newStatus)
    {
        _status = newStatus;
        KoSOM_TriggerStatus.value(_status, DPT_Switch);
    }
}
