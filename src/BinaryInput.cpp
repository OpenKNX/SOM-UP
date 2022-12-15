#include "BinaryInput.h"

BinaryInput::BinaryInput(uint8_t iIndex, uint8_t iInputPin, int8_t iPulsePin)
{
  this->mIndex = iIndex;
  this->mInputPin = iInputPin;
  this->mPulsePin = iPulsePin;
}
BinaryInput::~BinaryInput() {}

uint32_t BinaryInput::calcParamIndex(uint16_t iParamIndex)
{
  return iParamIndex + mIndex * BI_ParamBlockSize + BI_ParamBlockOffset;
}

uint16_t BinaryInput::calcKoNumber(uint8_t iKoIndex)
{
  return iKoIndex + mIndex * BI_KoBlockSize + BI_KoOffset;
}

int8_t BinaryInput::calcKoIndex(uint16_t iKoNumber)
{
  int16_t result = (iKoNumber - BI_KoOffset);
  // check if channel is valid
  if ((int8_t)(result / BI_KoBlockSize) == mIndex)
    result = result % BI_KoBlockSize;
  else
    result = -1;
  return (int8_t)result;
}

GroupObject *BinaryInput::getKo(uint8_t iKoIndex)
{
  return &knx.getGroupObject(calcKoNumber(iKoIndex));
}

void BinaryInput::setup()
{
  // Params
  mParamActive = (knx.paramByte(calcParamIndex(BI_InputActive)) & BI_InputActiveMask) >> BI_InputActiveShift;
  mParamMode = (knx.paramByte(calcParamIndex(BI_InputMode)) & BI_InputModeMask) >> BI_InputModeShift;
  mParamDebouncing = (knx.paramByte(calcParamIndex(BI_InputDebouncing)));
  mParamPeriodic = (getDelayPattern(calcParamIndex(BI_InputPeriodicBase)));

  getKo(BI_KoInputOutput)->valueNoSend(false, getDPT(VAL_DPT_1));

  // Debug
  SERIAL_DEBUG.printf("BE %i mParamActive: %i\n\r", mIndex, mParamActive);
  SERIAL_DEBUG.printf("BE %i mParamMode: %i\n\r", mIndex, mParamMode);
  SERIAL_DEBUG.printf("BE %i mParamDebouncing: %i\n\r", mIndex, mParamDebouncing);
  SERIAL_DEBUG.printf("BE %i mParamPeriodic: %i\n\r", mIndex, mParamPeriodic);
}
void BinaryInput::loop()
{
  if (mParamActive != 1)
    return;

  processInput();
  processPeriodicSend();
}

bool BinaryInput::queryInput()
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

void BinaryInput::processInput()
{
  // pulsed query
  if (!checkQueryTime())
    return;

  bool lState = queryInput();

  // Skip till debounced
  if (debounced(lState))
    return;

  if (lState != mCurrentState)
  {
    SERIAL_DEBUG.printf("BE %i: %i\n\r", mIndex, lState);
    mCurrentState = lState;
    sendState();
  }
}

bool BinaryInput::debounced(bool iCurrentState)
{
  if (iCurrentState != mLastButtonState)
  {
    mLastDebounceTime = millis();
    mLastButtonState = iCurrentState;
  }

  if ((millis() - mLastDebounceTime) > mParamDebouncing)
  {
    mLastButtonState = iCurrentState;
    return false;
  }

  return true;
}

bool BinaryInput::checkQueryTime()
{
  if ((millis() - mLastQueryTime) > BI_QueryDelay)
  {
    mLastQueryTime = millis();
    return true;
  }

  return false;
}

void BinaryInput::processPeriodicSend()
{
  if (mParamPeriodic == 0)
    return;

  if ((millis() - mLastPeriodicSend) > mParamPeriodic)
  {
    mLastPeriodicSend = millis();
    sendState();
  }
}

void BinaryInput::sendState()
{
  bool lSendState = mParamMode ? !mCurrentState : mCurrentState;
  getKo(BI_KoInputOutput)->value(lSendState, getDPT(VAL_DPT_1));
}
