#pragma once

#ifdef HARDWARE_PLAYER
    #include "SoundPlayer.h"
    #include "hardware.h"

    #define PLAYER_STATUS_WATCHDOG 1000
    #define PLAYER_STATUS_PLAYING 1
    #define PLAYER_STATUS_STOPPED 1
    #define PLAYER_DATA_BEGIN 0xAA

class SoundPlayerHardware : public SoundPlayer
{
  private:
    uint8_t _currentVolume = 0;
    bool _playerAvailable = false;
    uint32_t _lastReceivedStatus = 0;
    uint32_t _monitorHardwareStatus = 0;
    uint32_t _receiveStatusSince = 0;
    uint32_t _lastRequestStatus = 0;
    uint8_t _receivedStatusPos = 0;
    uint8_t _receivedStatusBuffer[5];
    bool _receivedStatus = false;

    uint8_t calcChecksum(uint8_t *data, uint8_t len);
    bool validateChecksum(uint8_t *data, uint8_t len);
    void sendData(uint8_t *data, uint8_t len);

    void processMonitorHardwareStatus();

    void playNextPlay() override;
    void playFileNumber(uint16_t file) override;

    void requestStatus();
    void processStatus();

    void processStatusStopped() override;
    void processStatusPlaying() override;

    void configureRepeats(uint16_t repeats);
    void configureVolume(uint8_t volume);
    void stopCurrentPlay();

  public:
    void setup() override;
    void loop() override;
    void powerOn() override;
    void powerOff() override;

    void setInitialVolume(uint8_t volume) override { configureVolume(volume); };
};
#endif