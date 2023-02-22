#include "SoundTrigger.h"
#include "SoundModule.h"

SoundTrigger::SoundTrigger(uint8_t index)
{
    _channelIndex = index;
}

const std::string SoundTrigger::name()
{
    return "SoundTrigger";
}

void SoundTrigger::setup()
{
    _currentVolume = ParamSOM_TriggerVolumeDay;
    _currentFile = ParamSOM_TriggerFileDay;
    KoSOM_TriggerStatus.valueNoSend(false, DPT_Switch);
    KoSOM_TriggerLock.valueNoSend(false, DPT_Switch);

    // Debug
    logTraceP("paramActive: %i", ParamSOM_TriggerState);
    logTraceP("paramRepeats: %i", ParamSOM_TriggerRepeats);
    logTraceP("paramPriority: %i", ParamSOM_TriggerPriority);
    logTraceP("paramLock: %i", ParamSOM_TriggerLock);
    logTraceP("paramDayNight: %i", ParamSOM_TriggerDayNight);
    logTraceP("paramVolumeDay: %i", ParamSOM_TriggerVolumeDay);
    logTraceP("paramVolumeNight: %i", ParamSOM_TriggerVolumeNight);
    logTraceP("paramFileDay: %i", ParamSOM_TriggerFileDay);
    logTraceP("paramFileNight: %i", ParamSOM_TriggerFileNight);
    logTraceP("paramDurationMS: %i", ParamSOM_TriggerDurationTimeMS);
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
    logInfoP("lock");
}

void SoundTrigger::unlock()
{
    if (ParamSOM_TriggerLock == 0 || !_currentLocked)
        return;

    _currentLocked = false;
    KoSOM_TriggerLock.value(_currentLocked, DPT_Switch);
    logInfoP("unlock");
}

void SoundTrigger::day()
{
    logInfoP("day mode");
    _currentVolume = ParamSOM_TriggerVolumeDay;
    _currentFile = ParamSOM_TriggerFileDay;
}

void SoundTrigger::night()
{
    logInfoP("night mode");
    _currentVolume = ParamSOM_TriggerVolumeNight;
    _currentFile = ParamSOM_TriggerFileNight;
}

void SoundTrigger::play()
{
    if (_currentLocked)
    {
        logInfoP("play ignored (locked)");
        return;
    }
    logInfoP("play");
    setStatus(SoundModule::instance()->play(_currentFile, _currentVolume, ParamSOM_TriggerPriority, ParamSOM_TriggerRepeats, ParamSOM_TriggerDurationTimeMS, _channelIndex));
}

void SoundTrigger::stop()
{
    // skip if not playing
    if (!_status)
        return;

    logInfoP("stop");
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
