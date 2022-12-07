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
  hardware = DY::Player(&Serial2);
  hardware.begin();

  delay(100);
  hardware.stop();
  SERIAL_DEBUG.println("SoundPlayer::setup ready");
}

void SoundPlayer::play(uint8_t file, uint8_t volume, bool repeat)
{
  SERIAL_DEBUG.printf("SoundPlayer::play %i - %i\n\r", file, volume);
  status = true;
  waitForPlaying = true;

  // Volume
  setVolume(volume);

  // stop
  hardware.stop();

  // Repeat
  if (repeat) {
    hardware.setCycleMode(DY::PlayMode::RepeatOne);
  } else {
    hardware.setCycleMode(DY::PlayMode::OneOff);
  }

  std::stringstream filepath;
  filepath << "/" << std::setfill('0') << std::setw(5) << std::to_string(file) << "*MP3";
  // SERIAL_DEBUG.printf("SoundPlayer::path %s\n\r", filepath.str().c_str());
  hardware.playSpecifiedDevicePath(DY::Device::Flash, (char *)filepath.str().c_str());
  //_dyplayer.playSpecified(file);

  // reset for next check in 250ms
  previousMillis = millis();
}

void SoundPlayer::setVolume(uint8_t volume)
{
  // invalid volume
  if (volume < 1 || volume > 30)
    return;

  // volume already set
  if (volume == lastVolume)
    return;

  // update volume
  SERIAL_DEBUG.printf("SoundPlayer::setVolume %i\n\r", volume);
  lastVolume = volume;
  hardware.setVolume(volume);
}

void SoundPlayer::loop()
{
  requestStatus();
  processStatus();
}

void SoundPlayer::requestStatus()
{
  // wait already for status
  if (waitForState)
    return;

  // check only every 250ms
  if ((millis() - previousMillis) < 250)
    return;

  previousMillis = millis();
  uint8_t msg[] = {0xAA, 0x01, 0x00, 0xAB};
  Serial2.write(msg, sizeof(msg));
  waitForState = true;
}

void SoundPlayer::processStatus()
{
  // do waiting for status and new byte is available
  if (waitForState && Serial2.available())
  {
    // read byte into buffer
    responseStateBuffer[responseStatePos] = Serial2.read();
    responseStatePos++;

    // Response is completed (all 5 bytes recevied)
    if (responseStatePos == 5)
    {
      // POSSIBLE IMPROVEMENT: Validate checksum - not needed yet - only check responsed
      if (status && responseStateBuffer[3] != 1)
        waitForPlaying = false;

      // status is playing and response is stopped
      if (status && responseStateBuffer[3] == 0)
      {
        status = false;
        SoundControl::instance->stopped();
      }

      // Reset for next requestStatus
      responseStatePos = 0;
      waitForState = false;
    }
  }
  // POSSIBLE IMPROVEMENT: Check response took to long. then reset
}

void SoundPlayer::stop()
{
  SERIAL_DEBUG.println("SoundPlayer::stop");
  hardware.stop();
}