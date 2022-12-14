#include "SoundControl.h"
#include "SoundPlayer.h"
#include "hardware.h"

SoundPlayer::SoundPlayer()
{
}
SoundPlayer::~SoundPlayer() {}

void SoundPlayer::powerOn()
{
#ifdef PLAYER_PWR
  SERIAL_DEBUG.println("poweron player...");
  digitalWrite(PLAYER_PWR, HIGH);
#endif
}
void SoundPlayer::powerOff()
{
  SERIAL_DEBUG.println("poweroff player...");
#ifdef PLAYER_PWR
  digitalWrite(PLAYER_PWR, LOW);
#endif
}

void SoundPlayer::setup()
{
#ifdef PLAYER_PWR
  pinMode(PLAYER_PWR, OUTPUT);
  powerOn();
#endif

  // setup hardware serial
  SERIAL_DEBUG.println("SoundPlayer::setup start");
  Serial2.setRX(PLAYER_UART_RX_PIN);
  Serial2.setTX(PLAYER_UART_TX_PIN);
  Serial2.begin(9600);

  delay(50);
  stop(true);

  SERIAL_DEBUG.println("SoundPlayer::setup ready");
}

void SoundPlayer::play(uint16_t iFile, uint8_t iVolume, uint32_t iRepeats, uint32_t iDuration)
{
  SERIAL_DEBUG.printf("SoundPlayer::play %i/%i/%i/%i\n\r", iFile, iVolume, iRepeats, iDuration);

  mNextPlay.file = iFile;
  mNextPlay.volume = iVolume;
  mNextPlay.duration = iDuration;
  mNextPlay.repeats = iRepeats;
  mNextPlay.playMillis = millis();

  // Stop current if needed
  if (mPlaying)
    stop();
}

// Internal play
void SoundPlayer::play(Play &iPlay)
{
  // set volume
  setVolume(iPlay.volume);

  // set repeats
  setRepeats(iPlay.repeats);

  // play file
  playFileNumber(iPlay.file);
}

void SoundPlayer::setVolume(uint8_t iVolume)
{
  // invalid volume
  if (iVolume < 1 || iVolume > 30)
    return;

  // volume already set
  if (iVolume == mLastVolume)
    return;

  // update volume
  SERIAL_DEBUG.printf("SoundPlayer::setVolume %i\n\r", iVolume);
  mLastVolume = iVolume;

  uint8_t data[] = {0xAA, 0x13, 0x01, iVolume};
  sendData(data, 4);
}

void SoundPlayer::loop()
{
  requestStatus();
  processStatus();
  processDuration();
  processNextPlay();
}

void SoundPlayer::processNextPlay()
{
  // Already playing
  if (mPlaying)
    return;

  // No next play
  if (mNextPlay.file == 0)
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processNextPlay: %i (%i)\n\r", mNextPlay.file, (millis() - mNextPlay.playMillis));

  play(mNextPlay);

  mCurrentPlay = mNextPlay;
  mNextPlay = SoundPlayer::Play();
}

void SoundPlayer::processDuration()
{
  if (mStopping)
    return;

  if (mCurrentPlay.duration == 0)
    return;

  if (mCurrentPlay.playingMillis == 0)
    return;

  if (!delayCheck(mCurrentPlay.playingMillis, mCurrentPlay.duration))
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processDuration %i/%i/%i\n\r", millis(), mCurrentPlay.playingMillis, mCurrentPlay.duration);
  stop();
}

void SoundPlayer::requestStatus()
{
  // skip when you send request
  if (!delayCheck(mLastRequestStatus, 100))
    return;

  if (!delayCheck(mLastReceivedStatus, 50))
    return;

  mLastRequestStatus = millis();
  mLastReceivedStatus = 0;
  uint8_t data[] = {0xAA, 0x01, 0x00};
  sendData(data, 3);
}

void SoundPlayer::processStatus()
{
  uint8_t lReceivedChar;

  while (Serial2.available())
  {
    lReceivedChar = Serial2.read();

    if (lReceivedChar == 0xAA)
    {
      mReceivedStatusPos = 0;
      mReceiveStatusSince = millis();
      mPlayerAvailable = true;
    }

    if (mReceiveStatusSince > 0)
    {
      mReceivedStatusBuffer[mReceivedStatusPos] = lReceivedChar;
      mReceivedStatusPos++;
    }

    // Response is completed (all 5 bytes recevied)
    if (mReceivedStatusPos == 5)
    {
      mReceiveStatusSince = 0;
      mReceivedStatusPos = 0;
      mLastRequestStatus = 0;
      mLastReceivedStatus = millis();
      //printHEX("recevied status: ", mReceivedStatusBuffer, 5);

      if (validateChecksum(mReceivedStatusBuffer, 5))
      {
        switch (mReceivedStatusBuffer[3])
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
        printHEX("SoundPlayer::processStatus invalid checksum", mReceivedStatusBuffer, 5);
      }
    }
  }
}

void SoundPlayer::processStatusStopped()
{
#ifdef PLAYER_BUSY_PIN
  digitalWrite(PLAYER_BUSY_PIN, LOW);
#endif
  mReceivedStatus = false;

  // Already Stopped
  if (!mPlaying)
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processStatusStopped: %i\n\r", (millis() - mCurrentPlay.playingMillis));

  if (mNextPlay.file == 0)
    SoundControl::sInstance->stopped();

  mStopping = false;
  mPlaying = false;
  mCurrentPlay = SoundPlayer::Play();
}

void SoundPlayer::processStatusPlaying()
{
#ifdef PLAYER_BUSY_PIN
  digitalWrite(PLAYER_BUSY_PIN, HIGH);
#endif
  mReceivedStatus = true;

  // Already Playing
  if (mPlaying)
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processStatusPlaying: %i\n\r", (millis() - mCurrentPlay.playMillis));

  mPlaying = true;
  mCurrentPlay.playingMillis = millis();
}

void SoundPlayer::stop(bool force)
{
  if (!force)
  {
    if (!mPlaying)
      return;

    if (mStopping)
      return;
  }

  SERIAL_DEBUG.println("SoundPlayer::stop");
  uint8_t data[] = {0xAA, 0x04, 0x00};
  sendData(data, 3);

  if (mPlaying)
    mStopping = true;
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

void SoundPlayer::setRepeats(uint16_t iRepeats)
{
  uint8_t data[4] = {0xAA, 0x18, 0x01, 0x01};
  sendData(data, 4);
  
  iRepeats++;
  uint8_t data2[5] = {0xAA, 0x19, 0x02, 0x00, 0x00};
  data2[3] = iRepeats >> 8;
  data2[4] = iRepeats & 0xff;
  sendData(data2, 5);
}

void SoundPlayer::playFileNumber(uint16_t iFile)
{
  // 10 Bytes /00000.MP3
  std::stringstream lFilePathBuild;
  lFilePathBuild << "/" << std::setfill('0') << std::setw(5) << std::to_string(iFile) << "*MP3";
  const std::string lFilePath = lFilePathBuild.str();

  // 14 = 4 CMD + 10 PATH
  uint8_t data[14] = {0xAA, 0x08, 11 /* len + 1 */, 0x02};
  uint8_t lCopyPos = 4;
  for (char const &c : lFilePath)
  {
    data[lCopyPos] = c;
    lCopyPos++;
  }
  sendData(data, 14);
}