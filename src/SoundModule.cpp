#include "SoundModule.h"

SoundModule *SoundModule::_instance = nullptr;

SoundModule::SoundModule()
{
    SoundModule::_instance = this;
}

SoundModule *SoundModule::instance()
{
    return SoundModule::_instance;
}

const std::string SoundModule::name()
{
    return "Sound";
}

const std::string SoundModule::version()
{
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
}

#ifdef OPENKNX_DUALCORE
void SoundModule::loop1(bool configured)
{
    _player.loop();
};

void SoundModule::setup1(bool configured)
{
    _player.setup();
};
#endif

void SoundModule::setup(bool configured)
{
#ifndef OPENKNX_DUALCORE
    _player.setup();
#endif
    _currentDefaultVolume = 10;

    if (configured)
    {
        _currentDefaultVolume = ParamSOM_VolumeDay;

        // Default
        KoSOM_Status.valueNoSend(false, DPT_Switch);
        KoSOM_File.valueNoSend(false, DPT_Switch);
        KoSOM_Lock.valueNoSend(false, DPT_Switch);

        // Debug
        logTraceP("paramScenes: %i", ParamSOM_Scenes);
        logTraceP("paramExternal: %i", ParamSOM_External);
        logTraceP("paramLock: %i", ParamSOM_Lock);
        logTraceP("paramDayNight: %i", ParamSOM_DayNight);
        logTraceP("paramVolumeDay: %i", ParamSOM_VolumeDay);
        logTraceP("paramVolumeNight: %i", ParamSOM_VolumeNight);
        logTraceP("paramVolumeDay: %i", ParamSOM_VolumeDay);

        for (uint8_t i = 0; i < SOM_ChannelCount; i++)
        {
            _triggers[i] = new SoundTrigger(i);
            _triggers[i]->setup();
        }
    }
}

bool SoundModule::play(uint16_t file, uint8_t volume, uint8_t priority, uint32_t repeats, uint32_t duration, uint8_t trigger)
{
    // abort on lock
    if (_currentLocked)
    {
        logInfoP("play ignore -> lock");
        return false;
    }

    // skip if higher prio while playing
    if (_status && _lastPriority > priority)
    {
        logInfoP("play ignore -> prio");
        return false;
    }

    // use default volume if zero
    if (volume == 0) volume = _currentDefaultVolume;

    // reset states
    if (_status) SoundModule::stopped();

    logInfoP("play: file: %i  volume: %i:", file, volume);
    logIndentUp();

    // play music
    _player.play(file, volume, repeats, duration);

    // send ko
    if (knx.configured())
    {
        KoSOM_Status.value(true, DPT_Switch);
        KoSOM_File.value(file, DPT_Value_2_Ucount);
    }

    // save status
    _status = true;
    _lastFile = file;
    _lastVolume = volume;
    _lastPriority = priority;
    _lastTrigger = trigger;

    logIndentDown();
    return true;
}

void SoundModule::stop()
{
    logInfoP("stop");
    _player.stop();
}

/*
 * May be called by core 1. Therefore only simple operations that do not need a mutex may be executed.
 */
void SoundModule::stopped()
{
    if(!_status) return;
    if (!knx.configured()) return;

    logInfoP("stopped");
    _status = false;

    for (uint8_t i = 0; i < SOM_ChannelCount; i++)
    {
        SoundTrigger *trigger = _triggers[i];
        trigger->stopped();
    }

    KoSOM_Status.value(false, DPT_Switch);
    KoSOM_File.value((uint8_t)0, DPT_Value_2_Ucount);
}

void SoundModule::loop(bool configured)
{
#ifndef OPENKNX_DUALCORE
    _player.loop();
#endif

    if (configured)
    {
        uint8_t processed = 0;
        do
            _triggers[_currentTrigger]->loop();

        while (openknx.freeLoopIterate(SOM_ChannelCount, _currentTrigger, processed));
    }
}

void SoundModule::lock()
{
    if (ParamSOM_Lock == 0 || _currentLocked) return;

    _currentLocked = true;
    stop();
    KoSOM_Lock.value(_currentLocked, DPT_Switch);
    logInfoP("lock");
}

void SoundModule::unlock()
{
    if (ParamSOM_Lock == 0 || !_currentLocked) return;

    _currentLocked = false;
    KoSOM_Lock.value(_currentLocked, DPT_Switch);
    logInfoP("unlock");
}

void SoundModule::day()
{
    logInfoP("day mode");
    _currentNight = false;
    setDefaultVolume();
}

void SoundModule::night()
{
    logInfoP("night mode");
    _currentNight = true;
    setDefaultVolume();
}

void SoundModule::processInputKo(GroupObject &ko)
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
            if (asap >= SOM_KoOffset && asap < SOM_KoOffset + SOM_ChannelCount * SOM_KoBlockSize)
            {
                uint8_t i = (asap - SOM_KoOffset) / SOM_KoBlockSize;
                _triggers[i]->processInputKo(ko);
            }
            break;
    }
}

void SoundModule::processInputKoLock(GroupObject &ko)
{
    bool value = ko.value(DPT_Switch);

    if (ParamSOM_Lock == 1 && value == 1 || ParamSOM_Lock == 2 && value == 0)
        return lock();

    return unlock();
}
void SoundModule::processInputKoDayNight(GroupObject &ko)
{
    bool value = ko.value(DPT_Switch);

    if (ParamSOM_DayNight == 1 && value == 0 || ParamSOM_DayNight == 2 && value == 1)
        return night();

    return day();
}

void SoundModule::processInputKoScene(GroupObject &ko)
{
    if (!ParamSOM_Scenes)
        return;

    uint8_t value = ko.value(DPT_SceneNumber);
    value += 1;

    if (value > 0 && value <= 64)
    {
        for (uint8_t i = 0; i < 20; i++)
        {
            uint8_t sceneId = knx.paramByte(SOM_Scene0 + i);
            if (value == sceneId)
            {
                logInfoP("Scene %i", value);
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
                    SoundTrigger *trigger = _triggers[sceneTarget];
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

void SoundModule::processInputKoExternalVolume(GroupObject &ko)
{
    uint8_t value = ko.value(DPT_DecimalFactor);

    // invalid volume
    if (value < 0 || value > 30)
        value = 0;

    _externalVolume = value;
}

void SoundModule::processInputKoExternalPriority(GroupObject &ko)
{
    uint8_t value = ko.value(DPT_DecimalFactor);

    // invalid volume
    if (value < 1 || value > 5)
        value = 3;

    _externalPriority = value;
}

void SoundModule::processInputKoExternalFile(GroupObject &ko)
{
    uint16_t file = ko.value(DPT_Value_2_Ucount);

    if (file == 0) return stop();

    // invalid volume
    if (file < 1 || file > 65535) return;

    play(file, _externalVolume, _externalPriority, false);
}

void SoundModule::setDefaultVolume()
{
    // Dont set during playing
    if (_status) return;

    // select _currentDefaultVolume
    if (_currentNight)
        _currentDefaultVolume = ParamSOM_VolumeNight;
    else
        _currentDefaultVolume = ParamSOM_VolumeDay;

    // update _currentDefaultVolume
    _player.setInitialVolume(_currentDefaultVolume);
}

void SoundModule::processBeforeRestart()
{
    _player.stop();
}

void SoundModule::processBeforeTablesUnload()
{
    _player.stop();
}

void SoundModule::savePower()
{
    _player.savePower();
}

bool SoundModule::restorePower()
{
    _player.restorePower();
    return true;
}

bool SoundModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.substr(0, 5) == "play " && cmd.length() > 5)
    {
        uint16_t file = std::stoi(cmd.substr(5, 10));
        if (file > 0)
        {
            logInfoP("Manually play the file %i", file);
            logIndentUp();
            play(file, 0, 5);
            logIndentDown();

            return true;
        }
    }
    else if (cmd.substr(0, 4) == "vol " && cmd.length() > 4)
    {
        uint8_t volume = std::stoi(cmd.substr(4, 4));
        if (volume > 0)
        {
            logInfoP("Change the default volume to %i", volume);
            _currentDefaultVolume = volume;

            return true;
        }
    }
    else if (cmd == "stop")
    {
        _player.stop();
        return true;
    }

    return false;
}

void SoundModule::showHelp()
{
    openknx.console.printHelpLine("play XXX", "Manually play the file");
    openknx.console.printHelpLine("stop", "Stop playing immediately");
    openknx.console.printHelpLine("vol XXX", "Change the default volume");
}