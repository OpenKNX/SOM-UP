#include "SoundControl.h"
#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
}
SoundPlayer::~SoundPlayer() {}

void SoundPlayer::setup()
{
  // setup hardware serial
  SERIAL_DEBUG.println("SoundPlayer::setup start");
  Serial2.setRX(PLAYER_UART_RX_PIN);
  Serial2.setTX(PLAYER_UART_TX_PIN);
  Serial2.begin(9600);

  // setup hardware
  mHardware = DY::Player(&Serial2);
  mHardware.begin();

  delay(100);
  mHardware.stop();
  SERIAL_DEBUG.println("SoundPlayer::setup ready");
}

void SoundPlayer::play(uint16_t iFile, uint8_t iVolume, bool iRepeat)
{
  SERIAL_DEBUG.printf("SoundPlayer::play %i - %i\n\r", iFile, iVolume);
  mStatus = true;
  mWaitForPlaying = true;
  mStartPlayMillis = millis();

  // Volume
  setVolume(iVolume);
  SERIAL_DEBUG.printf("SoundPlayer::play after vol: %i\n\r", (millis() - mStartPlayMillis));

  // stop
  // stop();
  // SERIAL_DEBUG.printf("SoundPlayer::play after stop: %i\n\r", (millis() - mStartPlayMillis));

  // Repeat
  if (iRepeat)
  {
    mHardware.setCycleMode(DY::PlayMode::RepeatOne);
  }
  else
  {
    mHardware.setCycleMode(DY::PlayMode::OneOff);
  }
  SERIAL_DEBUG.printf("SoundPlayer::play after cyclemode: %i\n\r", (millis() - mStartPlayMillis));

  std::stringstream lFilepath;
  lFilepath << "/" << std::setfill('0') << std::setw(5) << std::to_string(iFile) << "*MP3";
  // SERIAL_DEBUG.printf("SoundPlayer::path %s\n\r", lFilepath.str().c_str());
  mHardware.playSpecifiedDevicePath(DY::Device::Flash, (char *)lFilepath.str().c_str());
  //_dyplayer.playSpecified(iFile);
  SERIAL_DEBUG.printf("SoundPlayer::play after play: %i\n\r", (millis() - mStartPlayMillis));

  // reset for next check in 250ms
  mPreviousMillis = millis();
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
  mHardware.setVolume(iVolume);
}

void SoundPlayer::loop()
{
  requestStatus();
  processStatus();
}

void SoundPlayer::requestStatus()
{
  // wait already for status
  if (mWaitForState)
    return;

  // check only every 250ms
  if ((millis() - mPreviousMillis) < 250)
    return;

  mPreviousMillis = millis();
  uint8_t lMsg[] = {0xAA, 0x01, 0x00, 0xAB};
  Serial2.write(lMsg, sizeof(lMsg));
  mWaitForState = true;
}

void SoundPlayer::processStatus()
{
  // do waiting for status and new byte is available
  if (mWaitForState && Serial2.available())
  {
    // read byte into buffer
    mResponseStateBuffer[mResponseStatePos] = Serial2.read();
    mResponseStatePos++;

    // Response is completed (all 5 bytes recevied)
    if (mResponseStatePos == 5)
    {
      // POSSIBLE IMPROVEMENT: Validate checksum - not needed yet - only check responsed

      // Check Status Changed
      if (!mLastHardwareStatus && mResponseStateBuffer[3] == 1)
      {
        SERIAL_DEBUG.printf("SoundPlayer::processStatus: play %i\n\r", (millis() - mStartPlayMillis));
        mLastHardwareStatus = true;
      }

      if (mLastHardwareStatus && mResponseStateBuffer[3] == 0)
      {
        SERIAL_DEBUG.printf("SoundPlayer::processStatus: stop %i\n\r", (millis() - mStartPlayMillis));
        mLastHardwareStatus = false;
      }

      if (mStatus && mResponseStateBuffer[3] != 1)
        mWaitForPlaying = false;

      // status is playing and response is stopped
      if (mStatus && mResponseStateBuffer[3] == 0)
      {
        mStatus = false;
        SoundControl::sInstance->stopped();
        SERIAL_DEBUG.printf("SoundPlayer::processStatus after stop: %i\n\r", (millis() - mStartPlayMillis));
      }

      // Reset for next requestStatus
      mResponseStatePos = 0;
      mWaitForState = false;
    }
    // POSSIBLE IMPROVEMENT: Check response took to long. then reset
  }
}

void SoundPlayer::stop()
{
  SERIAL_DEBUG.println("SoundPlayer::stop");

  if (!mStatus)
    return;

  //mHardware.stop();
}