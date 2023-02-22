#include "SoundPlayer.h"
#include "SoundModule.h"

std::string SoundPlayer::logPrefix()
{
    return "SoundPlayer";
}

void SoundPlayer::powerOn()
{
    _statusLed.powerSave(false);
#ifdef PLAYER_PWR
    logTraceP("poweron player");
    digitalWrite(PLAYER_PWR, HIGH);
    delay(1000);
#endif
    _powerOff = false;
}
void SoundPlayer::powerOff()
{
    _statusLed.powerSave(true);
#ifdef PLAYER_PWR
    logTraceP("poweroff player");
    digitalWrite(PLAYER_PWR, LOW);
#endif
    processStatusStopped();
    _lastVolume = 0;
    _playing = false;
    _stopping = false;
    _powerOff = true;
}

void SoundPlayer::setup()
{

#ifdef PLAYER_BUSY_PIN
    logTraceP("init player led");
    _statusLed.init(PLAYER_BUSY_PIN);
#endif

#ifdef PLAYER_PWR
    pinMode(PLAYER_PWR, OUTPUT);
    powerOn();
#endif

    // setup hardware serial
    logTraceP("init player");
    Serial2.setRX(PLAYER_UART_RX_PIN);
    Serial2.setTX(PLAYER_UART_TX_PIN);
    Serial2.begin(9600);

    delay(50);
    stop(true);
    logTraceP("   init player completed");
}

void SoundPlayer::play(uint16_t file, uint8_t volume, uint32_t repeats, uint32_t duration)
{
    if (_powerOff)
    {
        logTraceP("no play - player is powered off");
        SoundModule::instance()->stopped();
        return;
    }

    logTraceP("play %i/%i/%i/%i", file, volume, repeats, duration);

    _nextPlay.file = file;
    _nextPlay.volume = volume;
    _nextPlay.duration = duration;
    _nextPlay.repeats = repeats;
    _nextPlay.playMillis = millis();

    // Stop current if needed
    if (_playing)
        stop();
}

// Internal play
void SoundPlayer::play(Play &play)
{
    // set volume
    setVolume(play.volume);

    // set repeats
    setRepeats(play.repeats);

    // play file
    playFileNumber(play.file);
}

void SoundPlayer::setVolume(uint8_t volume)
{
    // invalid volume
    if (volume < 1 || volume > 30)
        return;

    // volume already set
    if (volume == _lastVolume)
        return;

    logTraceP("set volume %i", volume);

    // update volume
    _lastVolume = volume;

    uint8_t data[] = {0xAA, 0x13, 0x01, volume};
    sendData(data, 4);
}

void SoundPlayer::loop()
{
    _statusLed.loop();
    requestStatus();
    processStatus();
    processDuration();
    processNextPlay();
}

void SoundPlayer::processNextPlay()
{
    // Already playing
    if (_playing)
        return;

    // No next play
    if (_nextPlay.file == 0)
        return;

    logTraceP("processNextPlay %i (%i)", _nextPlay.file, (millis() - _nextPlay.playMillis));

    play(_nextPlay);

    _currentPlay = _nextPlay;
    _nextPlay = SoundPlayer::Play();
}

void SoundPlayer::processDuration()
{
    if (_stopping)
        return;

    if (_currentPlay.duration == 0)
        return;

    if (_currentPlay.playingMillis == 0)
        return;

    if (!delayCheck(_currentPlay.playingMillis, _currentPlay.duration))
        return;

    logTraceP("processDuration %i/%i/%i", millis(), _currentPlay.playingMillis, _currentPlay.duration);
    stop();
}

void SoundPlayer::requestStatus()
{
    if (_powerOff)
        return;

    // skip when you send request
    if (!delayCheck(_lastRequestStatus, 100))
        return;

    if (!delayCheck(_lastReceivedStatus, 50))
        return;

    _lastRequestStatus = millis();
    _lastReceivedStatus = 0;
    uint8_t data[] = {0xAA, 0x01, 0x00};
    sendData(data, 3);
}

void SoundPlayer::processStatus()
{
    if (_powerOff)
        return;

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

void SoundPlayer::processStatusStopped()
{
    _receivedStatus = false;

    // Already Stopped
    if (!_playing)
        return;

    _statusLed.off();

    logTraceP("processStatusStopped (%ims)", (millis() - _currentPlay.playingMillis));

    if (_nextPlay.file == 0)
        SoundModule::instance()->stopped();

    _stopping = false;
    _playing = false;
    _currentPlay = SoundPlayer::Play();
}

void SoundPlayer::processStatusPlaying()
{
    _receivedStatus = true;

    // Already Playing
    if (_playing)
        return;

    _statusLed.on();

    logTraceP("processStatusPlaying (%ims)", (millis() - _currentPlay.playMillis));

    _playing = true;
    _currentPlay.playingMillis = millis();
}

void SoundPlayer::stop(bool force)
{
    if (!force)
    {
        if (!_playing)
            return;

        if (_stopping)
            return;
    }

    logTraceP("stop");

    uint8_t data[] = {0xAA, 0x04, 0x00};
    sendData(data, 3);

    if (_playing)
        _stopping = true;
}

uint8_t SoundPlayer::calcChecksum(uint8_t *data, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
    {
        sum = sum + data[i];
    }
    return sum;
}

bool SoundPlayer::validateChecksum(uint8_t *data, uint8_t len)
{
    uint8_t crc = data[len - 1];
    return calcChecksum(data, len - 1) == crc;
}

void SoundPlayer::sendData(uint8_t *data, uint8_t len)
{
    Serial2.write(data, len);
    uint8_t checksum = calcChecksum(data, len);
    Serial2.write(checksum);
}

void SoundPlayer::setRepeats(uint16_t repeats)
{
    uint8_t data[4] = {0xAA, 0x18, 0x01, 0x01};
    sendData(data, 4);

    repeats++;
    uint8_t data2[5] = {0xAA, 0x19, 0x02, 0x00, 0x00};
    data2[3] = repeats >> 8;
    data2[4] = repeats & 0xff;
    sendData(data2, 5);
}

void SoundPlayer::playFileNumber(uint16_t file)
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