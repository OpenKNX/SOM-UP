#include "BinaryInputControl.h"

BinaryInputControl::BinaryInputControl() {}
BinaryInputControl::~BinaryInputControl() {}

void BinaryInputControl::setup()
{
  pinMode(BINARY_INPUT_A_PIN, INPUT);
  pinMode(BINARY_INPUT_B_PIN, INPUT);
  pinMode(BINARY_INPUT_C_PIN, INPUT);
  pinMode(BINARY_INPUT_D_PIN, INPUT);
#if defined(BINARY_INPUT_PULSE) && BINARY_INPUT_PULSE != -1
  pinMode(BINARY_INPUT_PULSE, OUTPUT);
#endif

  // Setup BE
  for (uint8_t i = 0; i < BI_ChannelCount; i++)
    mBinaryInputs[i]->setup();
}

void BinaryInputControl::loop()
{
  processHardwareInputs();

  for (uint8_t i = 0; i < BI_ChannelCount; i++)
    mBinaryInputs[i]->loop();
}

void BinaryInputControl::processHardwareInputs()
{
  if (
      !mBinaryInputs[0]->isActive() &&
      !mBinaryInputs[1]->isActive() &&
      !mBinaryInputs[2]->isActive() &&
      !mBinaryInputs[3]->isActive())
    return;

#if defined(BINARY_INPUT_PULSE) && BINARY_INPUT_PULSE != -1
  if (!delayCheck(mLastHardwareQuery, BINARY_INPUT_PULSE_PAUSE_TIME))
    return;

  digitalWrite(BINARY_INPUT_PULSE, true);
  busy_wait_us(500); // BINARY_INPUT_PULSE_WAIT_TIME);
#endif

  if (mBinaryInputs[0]->isActive())
    mBinaryInputs[0]->setHardwareState(digitalRead(BINARY_INPUT_A_PIN) == LOW);
  if (mBinaryInputs[1]->isActive())
    mBinaryInputs[1]->setHardwareState(digitalRead(BINARY_INPUT_B_PIN) == LOW);
  if (mBinaryInputs[2]->isActive())
    mBinaryInputs[2]->setHardwareState(digitalRead(BINARY_INPUT_C_PIN) == LOW);
  if (mBinaryInputs[3]->isActive())
    mBinaryInputs[3]->setHardwareState(digitalRead(BINARY_INPUT_D_PIN) == LOW);

#if defined(BINARY_INPUT_PULSE) && BINARY_INPUT_PULSE != -1
  digitalWrite(BINARY_INPUT_PULSE, false);
#endif
  mLastHardwareQuery = millis();
}