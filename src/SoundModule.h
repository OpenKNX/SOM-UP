#pragma once
#include "Helper.h"
#include "KnxHelper.h"
#include "SoundPlayer.h"
#include "SoundTrigger.h"

#define SOM_SceneActionStart 1
#define SOM_SceneActionStop 2
#define SOM_SceneActionLock 3
#define SOM_SceneActionUnlock 4

class SoundModule : public OpenKNX::Module
{

  public:
    SoundModule();
    void loop() override;
    void setup() override;
    const char *name() override;
    const char *version() override;
    void processInputKo(GroupObject &ko) override;
    bool play(uint16_t file, uint8_t volume = 0, uint8_t priority = 3, uint32_t repeats = 0, uint32_t duration = 0, uint8_t trigger = 0);
    void stop();
    void stopped();
    void lock();
    void unlock();
    void day();
    void night();
    static SoundModule *instance();

  private:
    static SoundModule *_instance;
    void processInputKoLock(GroupObject &ko);
    void processInputKoDayNight(GroupObject &ko);
    void processInputKoScene(GroupObject &ko);
    void processInputKoExternalVolume(GroupObject &ko);
    void processInputKoExternalPriority(GroupObject &ko);
    void processInputKoExternalFile(GroupObject &ko);
    void setDefaultVolume();
    void savePower() override;
    bool restorePower() override;
    SoundPlayer _player;
    SoundTrigger *_triggers[SOM_ChannelCount];
    bool _status = false;
    bool _currentNight = false;
    bool _currentLocked = false;
    uint8_t _currentDefaultVolume = 0;
    uint16_t _lastFile = 0;
    uint8_t _lastPriority = 0;
    uint8_t _lastVolume = 0;
    uint8_t _lastTrigger = 0;
    uint8_t _externalVolume = 0;
    uint8_t _externalPriority = 0;
};