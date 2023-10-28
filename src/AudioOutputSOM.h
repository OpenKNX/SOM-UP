#pragma once

#include "AudioOutputI2S.h"
#include "hardware.h"

/**
 * Auxiliary class for setting own default setting and inserting own SetVolume function
 */
class AudioOutputSOM : public AudioOutputI2S
{
  public:
    AudioOutputSOM() : AudioOutputI2S(44100L, (pin_size_t)PLAYER_I2S_BCLK_PIN, (pin_size_t)PLAYER_I2S_DATA_PIN) {}
    void SetVolume(uint8_t volume) { gainF2P6 = volume; }
};