#include "SoundControl.h"
#include "SoundPlayer.h"

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

  // setup hardware
  mHardware = DY::Player(&Serial2);
  mHardware.begin();

  // delay(100);
  mHardware.stop();
  SERIAL_DEBUG.println("SoundPlayer::setup ready");
}

void SoundPlayer::play(uint16_t iFile, uint8_t iVolume, uint32_t iDuration, bool iLoop)
{
  SERIAL_DEBUG.printf("SoundPlayer::play %i/%i/%i/%i\n\r", iFile, iVolume, iDuration, iLoop);

  mNextPlay.file = iFile;
  mNextPlay.volume = iVolume;
  mNextPlay.duration = iDuration;
  mNextPlay.loop = iLoop;
  mNextPlay.repeats = 1;
  mNextPlay.playMillis = millis();

  // Stop current if needed
  if (mPlaying)
    stop();
}

// Internal play
void SoundPlayer::play(Play &iPlay)
{
  if (iPlay.repeats > 0)
    iPlay.repeats -= 1;

  // set volume
  setVolume(iPlay.volume);

  // Repeat
  if (iPlay.loop)
    mHardware.setCycleMode(DY::PlayMode::RepeatOne);
  else
    mHardware.setCycleMode(DY::PlayMode::OneOff);

  // play file
  mHardware.playSpecifiedDevicePath(DY::Device::Flash, (char *)getFilePath(iPlay.file).c_str());
}

std::string SoundPlayer::getFilePath(uint16_t iFile)
{
  std::stringstream lFilePath;
  lFilePath << "/" << std::setfill('0') << std::setw(5) << std::to_string(iFile) << "*MP3";
  // SERIAL_DEBUG.printf("SoundPlayer::path %s\n\r", lFilePath.str().c_str());
  return lFilePath.str();
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
  watchdogStatus();
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
  if (
      !mStopping &&
      mCurrentPlay.duration > 0 &&
      mCurrentPlay.playingMillis > 0 &&
      delayCheck(mCurrentPlay.playingMillis, mCurrentPlay.duration))
  {
    SERIAL_DEBUG.printf("SoundPlayer::processDuration %i/%i/%i\n\r", millis(), mCurrentPlay.playingMillis, mCurrentPlay.duration);
    stop();
  }
}

// sound to loud and communication interruppted - internal reset
void SoundPlayer::watchdogStatus()
{
  if (!mWaitForState)
    return;

  // no status from player in Xms
  if (!delayCheck(mPreviousMillis, PLAYER_STATUS_WATCHDOG))
    return ;
  
  SERIAL_DEBUG.printf("SoundPlayer::watchdogStatus triggered\n\r");

  mWaitForState = false;
  mPreviousMillis = millis();
  mResponseStatePos = 0;
  mNextPlay.file = 0;
  mCurrentPlay.repeats = 0;
  mLastVolume = 0;
}

void SoundPlayer::requestStatus()
{
  // skip if wait already for response
  if (mWaitForState)
    return;

  // check only every Xms
  if (!delayCheck(mPreviousMillis, 5))
    return;

  mPreviousMillis = millis();
  uint8_t lMsg[] = {0xAA, 0x01, 0x00, 0xAB};
  Serial2.write(lMsg, sizeof(lMsg));
  mWaitForState = true;
  mResponseStatePos = 0;
}

void SoundPlayer::processStatus()
{
  uint32_t lTime = millis();
  uint16_t lI = 0;

  // allow 1ms for read data
  while (millis() - lTime <= 1)
  {
    lI += 1;
    if (!mWaitForState)
      return;

    if (!Serial2.available())
      return;

    // read byte into buffer
    mResponseStateBuffer[mResponseStatePos] = Serial2.read();
    mResponseStatePos++;

    // Response is completed (all 5 bytes recevied)
    if (mResponseStatePos == 5)
    {
      // POSSIBLE IMPROVEMENT: Validate checksum - not needed yet - only check responsed
      switch (mResponseStateBuffer[3])
      {
      case 1:
        processStatusPlaying();
        break;

      case 0:
        processStatusStopped();
        break;
      }

      // Reset for next requestStatus
      mResponseStatePos = 0;
      mWaitForState = false;
    }
    // POSSIBLE IMPROVEMENT: Check response took to long. then reset
  }
}

void SoundPlayer::processStatusStopped()
{
  // Already Stopped
  if (!mPlaying)
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processStatusStopped: %i\n\r", (millis() - mCurrentPlay.playingMillis));

  // Repeat
  if (mCurrentPlay.repeats > 0)
  {
    // mPlaying = false;
    play(mCurrentPlay);
    return;
  }

  if (mNextPlay.file == 0)
    SoundControl::sInstance->stopped();

  mStopping = false;
  mPlaying = false;
  mCurrentPlay = SoundPlayer::Play();
}

void SoundPlayer::processStatusPlaying()
{
  // Already Playing
  if (mPlaying)
    return;

  SERIAL_DEBUG.printf("SoundPlayer::processStatusPlaying: %i\n\r", (millis() - mCurrentPlay.playMillis));

  mPlaying = true;
  mCurrentPlay.playingMillis = millis();
}

void SoundPlayer::stop()
{
  SERIAL_DEBUG.println("SoundPlayer::stop");

  if (!mPlaying)
    return;

  if (mStopping)
    return;

  uint8_t lMsg[] = {0xAA, 0x04, 0x00, 0xAE};
  Serial2.write(lMsg, sizeof(lMsg));
  mStopping = true;
}