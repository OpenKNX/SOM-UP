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
    logTraceP("paramControl: %i", ParamSOM_TriggerControl);
    logTraceP("paramLock: %i", ParamSOM_TriggerLock);
    logTraceP("paramDayNight: %i", ParamSOM_TriggerDayNight);
    logTraceP("paramVolumeDay: %i", ParamSOM_TriggerVolumeDay);
    logTraceP("paramVolumeNight: %i", ParamSOM_TriggerVolumeNight);
    logTraceP("paramFileDay: %i", ParamSOM_TriggerFileDay);
    logTraceP("paramFileNight: %i", ParamSOM_TriggerFileNight);
    logTraceP("paramDurationMS: %i", ParamSOM_TriggerDurationTimeMS);
    logTraceP("paramReTrigger: %i", ParamSOM_TriggerReTrigger);
}

void SoundTrigger::processInputKo(GroupObject &ko)
{
    if (!ParamSOM_TriggerState) return;

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
    /* Control = 0 - Trigger 0 */
    if (ParamSOM_TriggerControl == 0 && !ko.value(DPT_Switch))
        return play();

    /* Control = 1 - Trigger 1 */
    if (ParamSOM_TriggerControl == 1 && ko.value(DPT_Switch))
        return play();

    /* Control = 2 - Start/Stopp */
    if (ParamSOM_TriggerControl == 2 && ko.value(DPT_Switch))
        return play();
    if (ParamSOM_TriggerControl == 2 && !ko.value(DPT_Switch))
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
    if (ParamSOM_TriggerLock == 0 || _currentLocked) return;

    _currentLocked = true;
    stop();
    KoSOM_TriggerLock.value(_currentLocked, DPT_Switch);
    logInfoP("lock");
}

void SoundTrigger::unlock()
{
    if (ParamSOM_TriggerLock == 0 || !_currentLocked) return;

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
    if (_status && ParamSOM_TriggerReTrigger)
    {
        logInfoP("play ignored (retrigger protection)");
        return;
    }
    logInfoP("play");
    logIndentUp();
    setStatus(openknxSoundModule.play(_currentFile, _currentVolume, ParamSOM_TriggerPriority, ParamSOM_TriggerRepeats, ParamSOM_TriggerDurationTimeMS, _channelIndex));
    logIndentDown();
}

void SoundTrigger::stop()
{
    // skip if not playing
    if (!_status) return;

    logInfoP("stop");
    setStatus(false);
    openknxSoundModule.stop();
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
