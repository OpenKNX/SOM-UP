#include "BinaryInputGPIO.h"
/*
BinaryInputGPIO::BinaryInputGPIO(uint8_t iIndex, uint8_t iInputPin, int8_t iPulsePin)
{
  mIndex = iIndex;
  mInputPin = iInputPin;
  mPulsePin = iPulsePin;
}

bool BinaryInputGPIO::queryHardwareInput()
{
  if (mPulsePin >= 0)
    digitalWrite(mPulsePin, true);

  bool lState = digitalRead(mInputPin);

  if (mPulsePin >= 0)
    digitalWrite(mPulsePin, false);

  if (lState == LOW)
    return true;

  return false;
}
*/