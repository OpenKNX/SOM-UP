#include "VirtualButton.h"

uint32_t VirtualButton::calcParamIndex(uint16_t iParamIndex)
{
  return iParamIndex + mIndex * BTN_ParamBlockSize + BTN_ParamBlockOffset;
}

uint16_t VirtualButton::calcKoNumber(uint8_t iKoIndex)
{
  return iKoIndex + mIndex * BTN_KoBlockSize + BTN_KoOffset;
}

int8_t VirtualButton::calcKoIndex(uint16_t iKoNumber)
{
  int16_t lResult = (iKoNumber - BTN_KoOffset);
  // check if channel is valid
  if ((int8_t)(lResult / BTN_KoBlockSize) == mIndex)
    lResult = lResult % BTN_KoBlockSize;
  else
    lResult = -1;
  return (int8_t)lResult;
}

GroupObject *VirtualButton::getKo(uint8_t iKoIndex)
{
  return &knx.getGroupObject(calcKoNumber(iKoIndex));
}

VirtualButton::VirtualButton(uint8_t iIndex)
{
  this->mIndex = iIndex;
}

void VirtualButton::setup()
{
  // Global Params
  mParams.mode = knx.paramByte(calcParamIndex(BTN_BTNMode));
  mParams.lock = (knx.paramByte(calcParamIndex(BTN_BTNLock)) & BTN_BTNLockMask) >> BTN_BTNLockShift;
  mParams.outputShort = knx.paramByte(calcParamIndex(BTN_BTNOutputShort));
  mParams.outputLong = knx.paramByte(calcParamIndex(BTN_BTNOutputLong));
  mParams.outputExtraLong = knx.paramByte(calcParamIndex(BTN_BTNOutputExtraLong));

  // Button 1 - Short
  mButtonParams[0].outputShort.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ShortDpt1) & BTN_BTNOutput1ShortDpt1Mask) >> BTN_BTNOutput1ShortDpt1Shift;
  mButtonParams[0].outputShort.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ShortDpt5));
  mButtonParams[0].outputShort.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ShortDpt5001));
  mButtonParams[0].outputShort.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ShortDpt17));

  // Button 1 - Long
  mButtonParams[0].outputLong.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput1LongDpt1) & BTN_BTNOutput1LongDpt1Mask) >> BTN_BTNOutput1LongDpt1Shift;
  mButtonParams[0].outputLong.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput1LongDpt5));
  mButtonParams[0].outputLong.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput1LongDpt5001));
  mButtonParams[0].outputLong.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput1LongDpt17));

  // Button 1 - ExtraLong
  mButtonParams[0].outputExtraLong.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ExtraLongDpt1) & BTN_BTNOutput1ExtraLongDpt1Mask) >> BTN_BTNOutput1ExtraLongDpt1Shift;
  mButtonParams[0].outputExtraLong.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ExtraLongDpt5));
  mButtonParams[0].outputExtraLong.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ExtraLongDpt5001));
  mButtonParams[0].outputExtraLong.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput1ExtraLongDpt17));

  // Button 2 - Short
  mButtonParams[1].outputShort.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ShortDpt1) & BTN_BTNOutput2ShortDpt1Mask) >> BTN_BTNOutput2ShortDpt1Shift;
  mButtonParams[1].outputShort.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ShortDpt5));
  mButtonParams[1].outputShort.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ShortDpt5001));
  mButtonParams[1].outputShort.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ShortDpt17));

  // Button 2 - Long
  mButtonParams[1].outputLong.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput2LongDpt1) & BTN_BTNOutput2LongDpt1Mask) >> BTN_BTNOutput2LongDpt1Shift;
  mButtonParams[1].outputLong.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput2LongDpt5));
  mButtonParams[1].outputLong.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput2LongDpt5001));
  mButtonParams[1].outputLong.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput2LongDpt17));

  // Button 2 - ExtraLong
  mButtonParams[1].outputExtraLong.dpt1 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ExtraLongDpt1) & BTN_BTNOutput2ExtraLongDpt1Mask) >> BTN_BTNOutput2ExtraLongDpt1Shift;
  mButtonParams[1].outputExtraLong.dpt5 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ExtraLongDpt5));
  mButtonParams[1].outputExtraLong.dpt5001 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ExtraLongDpt5001));
  mButtonParams[1].outputExtraLong.dpt17 = knx.paramByte(calcParamIndex(BTN_BTNOutput2ExtraLongDpt17));

  // Debug
  SERIAL_DEBUG.printf("BTN %i outputShortDpt1: %i/%i\n\r", mIndex, mButtonParams[0].outputShort.dpt1, calcParamIndex(BTN_BTNOutput1ShortDpt1));
  SERIAL_DEBUG.printf("BTN %i outputShortDpt5: %i/%i\n\r", mIndex, mButtonParams[0].outputShort.dpt5, calcParamIndex(BTN_BTNOutput1ShortDpt5));
  SERIAL_DEBUG.printf("BTN %i outputShortDpt5001: %i/%i\n\r", mIndex, mButtonParams[0].outputShort.dpt5001, calcParamIndex(BTN_BTNOutput1ShortDpt5001));
  SERIAL_DEBUG.printf("BTN %i outputShortDpt17: %i/%i\n\r", mIndex, mButtonParams[0].outputShort.dpt17, calcParamIndex(BTN_BTNOutput1ShortDpt17));

  SERIAL_DEBUG.printf("BTN %i mParamMode: %i\n\r", mIndex, mParams.mode);
}

void VirtualButton::loop()
{
  processPressAndHold(0);
  processPressAndHold(1);
  processMultiClick();
}

void VirtualButton::processInputKo(GroupObject &iKo)
{
  if (mParams.mode == 0)
    return;

  switch (calcKoIndex(iKo.asap()))
  {
  case BTN_KoBTNInput1:
    processInputKoInput(iKo, 0);
    break;
  case BTN_KoBTNInput2:
    processInputKoInput(iKo, 1);
    break;
  case BTN_KoBTNLock:
    processInputKoLock(iKo);
    break;
  }
}

void VirtualButton::processInputKoLock(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));
  // SERIAL_DEBUG.printf("BTN::processInputKoLock %i: %i\n\r", mIndex, lValue);
}

void VirtualButton::processInputKoInput(GroupObject &iKo, bool iButton)
{
  bool lNewPress = iKo.value(getDPT(VAL_DPT_1));
  bool lLastPress = mButtonState[iButton].press;

  // no state change
  if (lLastPress == lNewPress)
    return;

  if (lNewPress)
  {
    processPress(iButton);
  }
  else
  {
    processRelease(iButton);
  }
}

void VirtualButton::processPressAndHold(bool iButton)
{
  // not pressed
  if (!mButtonState[iButton].press)
    return;

  // no long press configured
  if (mParams.outputLong == 0)
    return;

  if (!mButtonState[iButton].pressLong && (millis() - mButtonState[iButton].pressStart) > BTN_LongPressTime)
  {
    eventLongPress(iButton);
    mButtonState[iButton].pressLong = true;
  }

  // no extra long press configured
  if (mParams.outputExtraLong == 0)
    return;

  if (!mButtonState[iButton].pressExtraLong && (millis() - mButtonState[iButton].pressStart) > BTN_ExtraLongPressTime)
  {
    eventExtraLongPress(iButton);
    mButtonState[iButton].pressExtraLong = true;
  }
}

void VirtualButton::processPress(bool iButton)
{
  if (mParams.mode == 2 && iButton == 0)
  {
    mButtonState[0].multiClicks += 1;
    mButtonState[0].multiClickTimer = millis();
    // SERIAL_DEBUG.printf("  BTN%i: mc press %i\n\r", iButton, mButtonState[0].multiClicks);
  }
  else
  {
    eventShortPress(iButton);
  }

  mButtonState[iButton].press = true;
  mButtonState[iButton].pressLong = false;
  mButtonState[iButton].pressExtraLong = false;
  mButtonState[iButton].pressStart = millis();
}

void VirtualButton::processRelease(bool iButton)
{
  if (mButtonState[iButton].pressExtraLong)
  {
    eventExtraLongRelease(iButton);
  }
  else if (mButtonState[iButton].pressLong)
  {
    eventLongRelease(iButton);
  }
  else if (mParams.mode == 2)
  {
    mButtonState[iButton].multiClickTimer = millis();
  }
  else
  {
    eventShortRelease(iButton);
  }

  // Reset MultiClick on Long or ExtraLong
  if (mButtonState[iButton].pressExtraLong || mButtonState[iButton].pressLong)
  {
    mButtonState[iButton].multiClicks = 0;
    mButtonState[iButton].multiClickTimer = 0;
  }

  // Reset all others
  mButtonState[iButton].press = false;
  mButtonState[iButton].pressLong = false;
  mButtonState[iButton].pressExtraLong = false;
  mButtonState[iButton].pressStart = 0;
}

void VirtualButton::processMultiClick()
{
  // no multiclick mode
  if (mParams.mode != 2)
    return;

  // skip during a press
  if (mButtonState[0].press)
    return;

  // skip when no timer started
  if (mButtonState[0].multiClickTimer == 0)
    return;

  if (millis() - mButtonState[0].multiClickTimer > BTN_MuliClickTime)
  {
    eventMultiClick(mButtonState[0].multiClicks);
    mButtonState[0].multiClickTimer = 0;
    mButtonState[0].multiClicks = 0;
  }
}

void VirtualButton::eventMultiClick(uint8_t iClicks)
{
  SERIAL_DEBUG.printf("  BTN%i: mc release %i\n\r", 0, iClicks);
  if (iClicks > BTN_MaxMuliClicks)
    return;
}
void VirtualButton::eventShortPress(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: short press\n\r", iButton);
}
void VirtualButton::eventLongPress(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: long press\n\r", iButton);
}
void VirtualButton::eventExtraLongPress(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: extra long press\n\r", iButton);
}
void VirtualButton::eventShortRelease(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: short release\n\r", iButton);
}
void VirtualButton::eventLongRelease(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: long release\n\r", iButton);
}
void VirtualButton::eventExtraLongRelease(bool iButton)
{
  SERIAL_DEBUG.printf("  BTN%i: extra long release\n\r", iButton);
}