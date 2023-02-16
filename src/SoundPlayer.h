#pragma once
#include "hardware.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include "OpenKNX/Led.h"

#define PLAYER_STATUS_WATCHDOG 1000
#define PLAYER_STATUS_PLAYING 1
#define PLAYER_STATUS_STOPPED 1
#define PLAYER_DATA_BEGIN 0xAA

class SoundControl;

class SoundPlayer
{

    struct Play
    {
        uint16_t file = 0;
        uint8_t volume = 0;
        uint32_t repeats = 1;
        uint32_t duration = 0;
        uint32_t playMillis = 0;
        uint32_t playingMillis = 0;
    };

  private:
    void processStatus();
    void requestStatus();
    void processDuration();
    void processStatusStopped();
    void processStatusPlaying();
    void processNextPlay();
    void play(Play &play);

    OpenKNX::Led _statusLed;

    bool _powerOff = false;
    bool _playing = false;
    bool _stopping = false;

    bool _playerAvailable = false;
    uint32_t _lastReceivedStatus = 0;
    uint32_t _receiveStatusSince = 0;
    uint32_t _lastRequestStatus = 0;
    uint8_t _receivedStatusPos = 0;
    uint8_t _receivedStatusBuffer[5];
    bool _receivedStatus = false;

    Play _currentPlay;
    Play _nextPlay;
    uint8_t _lastVolume = 0;

    uint8_t calcChecksum(uint8_t *data, uint8_t len);
    bool validateChecksum(uint8_t *data, uint8_t len);
    void sendData(uint8_t *data, uint8_t len);
    void setRepeats(uint16_t repeats = 1);
    void playFileNumber(uint16_t file);

  public:
    void setup();
    void play(uint16_t sound, uint8_t volume, uint32_t repeats = 0, uint32_t duration = 0);
    void stop(bool force = false);
    void loop();
    void setVolume(uint8_t volume);

    void powerOn();
    void powerOff();
};