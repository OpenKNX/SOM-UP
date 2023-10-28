#ifdef HARDWARE_PLAYER
    #include "SoundPlayerHardware.h"
    #include "SoundModule.h"

void SoundPlayerHardware::powerOn()
{
    SoundPlayer::powerOn();

    delay(1000);
}
void SoundPlayerHardware::powerOff()
{
    SoundPlayer::powerOff();

    processStatusStopped();
    _currentVolume = 0;
    _playing = false;
    _stopping = false;
}

void SoundPlayerHardware::setup()
{
    logInfoP("init hardware player");
    logIndentUp();

    SoundPlayer::setup();

    // setup hardware serial
    Serial2.setRX(PLAYER_UART_RX_PIN);
    Serial2.setTX(PLAYER_UART_TX_PIN);
    Serial2.begin(9600);

    delay(50);
    
    stopCurrentPlay();
    logTraceP("completed");
    logIndentDown();
}

void SoundPlayerHardware::configureVolume(uint8_t volume)
{
    // invalid volume
    if (volume < 1 || volume > 30) return;

    // volume already set
    if (volume == _currentVolume) return;

    logTraceP("set volume %i", volume);

    // update volume
    _currentVolume = volume;

    uint8_t data[] = {0xAA, 0x13, 0x01, volume};
    sendData(data, 4);
}

void SoundPlayerHardware::loop()
{
    if (_powerSave) return;

    processDuration();
    processStopping();
    requestStatus();
    processStatus();
    processNextPlay();
    processMonitorHardwareStatus();
}

void SoundPlayerHardware::processMonitorHardwareStatus()
{
    if (!delayCheck(_monitorHardwareStatus, 5000)) return;

    logErrorP("No response from mp3 player!");
    _monitorHardwareStatus = millis();
}

void SoundPlayerHardware::playNextPlay()
{
    // set volume
    configureVolume(_nextPlay.volume);

    // set repeats
    configureRepeats(_nextPlay.repeats);

    // play file
    playFileNumber(_nextPlay.file);
}

void SoundPlayerHardware::requestStatus()
{
    // skip when you send request
    if (!delayCheck(_lastRequestStatus, 100)) return;
    if (!delayCheck(_lastReceivedStatus, 50)) return;

    _lastRequestStatus = millis();
    _lastReceivedStatus = 0;
    uint8_t data[] = {0xAA, 0x01, 0x00};
    sendData(data, 3);
}

void SoundPlayerHardware::processStatus()
{
    uint8_t lReceivedChar;

    while (Serial2.available())
    {
        lReceivedChar = Serial2.read();

        if (lReceivedChar == 0xAA)
        {
            _receivedStatusPos = 0;
            _receiveStatusSince = millis();
            _playerAvailable = true;
        }

        if (_receiveStatusSince > 0)
        {
            _receivedStatusBuffer[_receivedStatusPos] = lReceivedChar;
            _receivedStatusPos++;
        }

        // Response is completed (all 5 bytes recevied)
        if (_receivedStatusPos == 5)
        {
            _receiveStatusSince = 0;
            _receivedStatusPos = 0;
            _lastRequestStatus = 0;
            _lastReceivedStatus = millis();
            _monitorHardwareStatus = millis();
            // printHEX("recevied status: ", _receivedStatusBuffer, 5);

            if (validateChecksum(_receivedStatusBuffer, 5))
            {
                switch (_receivedStatusBuffer[3])
                {
                    case 1:
                        processStatusPlaying();
                        break;

                    case 0:
                    case 2:
                        processStatusStopped();
                        break;
                }
            }
            else
            {
                logErrorP("processStatus invalid checksum");
                logHexErrorP(_receivedStatusBuffer, 5);
            }
        }
    }
}

void SoundPlayerHardware::processStatusStopped()
{
    _receivedStatus = false;

    SoundPlayer::processStatusStopped();
}

void SoundPlayerHardware::processStatusPlaying()
{
    _receivedStatus = true;

    SoundPlayer::processStatusPlaying();
}

void SoundPlayerHardware::stopCurrentPlay()
{
    uint8_t data[] = {0xAA, 0x04, 0x00};
    sendData(data, 3);
}

uint8_t SoundPlayerHardware::calcChecksum(uint8_t *data, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
        sum = sum + data[i];

    return sum;
}

bool SoundPlayerHardware::validateChecksum(uint8_t *data, uint8_t len)
{
    uint8_t crc = data[len - 1];
    return calcChecksum(data, len - 1) == crc;
}

void SoundPlayerHardware::sendData(uint8_t *data, uint8_t len)
{
    Serial2.write(data, len);
    uint8_t checksum = calcChecksum(data, len);
    Serial2.write(checksum);
}

void SoundPlayerHardware::configureRepeats(uint16_t repeats)
{
    uint8_t data[4] = {0xAA, 0x18, 0x01, 0x01};
    sendData(data, 4);

    repeats++;
    uint8_t data2[5] = {0xAA, 0x19, 0x02, 0x00, 0x00};
    data2[3] = repeats >> 8;
    data2[4] = repeats & 0xff;
    sendData(data2, 5);
}

void SoundPlayerHardware::playFileNumber(uint16_t file)
{
    // 10 Bytes /00000.MP3
    std::stringstream filePathBuild;
    filePathBuild << "/" << std::setfill('0') << std::setw(5) << std::to_string(file) << "*MP3";
    const std::string filePath = filePathBuild.str();

    // 14 = 4 CMD + 10 PATH
    uint8_t data[14] = {0xAA, 0x08, 11 /* len + 1 */, 0x02};
    uint8_t pos = 4;
    for (char const &c : filePath)
    {
        data[pos] = c;
        pos++;
    }
    sendData(data, 14);
}
#endif