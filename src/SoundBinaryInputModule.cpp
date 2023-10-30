#include "SoundBinaryInputModule.h"

const std::string SoundBinaryInputModule::name()
{
    return "SoundBinaryInput";
}

const std::string SoundBinaryInputModule::version()
{
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
}

void SoundBinaryInputModule::setup()
{
    pinMode(BINARY_INPUT_A_PIN, INPUT);
    pinMode(BINARY_INPUT_B_PIN, INPUT);
    pinMode(BINARY_INPUT_C_PIN, INPUT);
    pinMode(BINARY_INPUT_D_PIN, INPUT);
#if defined(BINARY_INPUT_PULSE_PIN) && BINARY_INPUT_PULSE_PIN != -1
    pinMode(BINARY_INPUT_PULSE_PIN, OUTPUT);
#endif

    // Setup BE
    for (uint8_t i = 0; i < BI_ChannelCount; i++)
        _channels[i]->setup();
}

void SoundBinaryInputModule::loop()
{
    processHardwareInputs();

    for (uint8_t i = 0; i < BI_ChannelCount; i++)
        _channels[i]->loop();
}

void SoundBinaryInputModule::processHardwareInputs()
{
    if (
        !_channels[0]->isActive() &&
        !_channels[1]->isActive() &&
        !_channels[2]->isActive() &&
        !_channels[3]->isActive())
        return;

#if defined(BINARY_INPUT_PULSE_PIN) && BINARY_INPUT_PULSE_PIN != -1
    if (!delayCheck(_lastHardwareQuery, BINARY_INPUT_PULSE_PAUSE_TIME))
        return;

    digitalWrite(BINARY_INPUT_PULSE_PIN, true);
    delayMicroseconds(BINARY_INPUT_PULSE_WAIT_TIME);
#endif

    if (_channels[0]->isActive())
        _channels[0]->setHardwareState(digitalRead(BINARY_INPUT_A_PIN) == LOW);
    if (_channels[1]->isActive())
        _channels[1]->setHardwareState(digitalRead(BINARY_INPUT_B_PIN) == LOW);
    if (_channels[2]->isActive())
        _channels[2]->setHardwareState(digitalRead(BINARY_INPUT_C_PIN) == LOW);
    if (_channels[3]->isActive())
        _channels[3]->setHardwareState(digitalRead(BINARY_INPUT_D_PIN) == LOW);

#if defined(BINARY_INPUT_PULSE_PIN) && BINARY_INPUT_PULSE_PIN != -1
    digitalWrite(BINARY_INPUT_PULSE_PIN, false);
#endif
    _lastHardwareQuery = millis();
}

SoundBinaryInputModule openknxSoundBinaryInputModule;