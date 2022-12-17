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

  mParams.eventShort = knx.paramByte(calcParamIndex(BTN_BTNOutputShortEvent));
  mParams.eventLong = knx.paramByte(calcParamIndex(BTN_BTNOutputLongEvent));
  mParams.eventExtraLong = knx.paramByte(calcParamIndex(BTN_BTNOutputExtraLongEvent));

  mButtonParams[0].outputShort = knx.paramByte(calcParamIndex(BTN_BTNOutput1ShortDpt1));
  mButtonParams[0].outputLong = knx.paramByte(calcParamIndex(BTN_BTNOutput1LongDpt1));
  mButtonParams[0].outputExtraLong = knx.paramByte(calcParamIndex(BTN_BTNOutput1ExtraLongDpt1));

  mButtonParams[1].outputShort = knx.paramByte(calcParamIndex(BTN_BTNOutput2ShortDpt1));
  mButtonParams[1].outputLong = knx.paramByte(calcParamIndex(BTN_BTNOutput2LongDpt1));
  mButtonParams[1].outputExtraLong = knx.paramByte(calcParamIndex(BTN_BTNOutput2ExtraLongDpt1));

  // Debug
  SERIAL_DEBUG.printf("BTN %i outputShort: %i/%i\n\r", mIndex, mButtonParams[0].outputShort, calcParamIndex(BTN_BTNOutput1ShortDpt1));
  SERIAL_DEBUG.printf("BTN %i outputLong: %i/%i\n\r", mIndex, mButtonParams[0].outputLong, calcParamIndex(BTN_BTNOutput1LongDpt1));
  SERIAL_DEBUG.printf("BTN %i outputExtraLong: %i/%i\n\r", mIndex, mButtonParams[0].outputExtraLong, calcParamIndex(BTN_BTNOutput1ExtraLongDpt1));

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
  if (mParams.eventShort != 1)
    return;

  SERIAL_DEBUG.printf("  BTN%i: short press\n\r", iButton);
  writeSwitchOutput(mParams.outputShort, mButtonParams[iButton].outputShort, BTN_KoBTNOutput1, BTN_KoBTNOutput1Status);
}
void VirtualButton::eventLongPress(bool iButton)
{
  if (mParams.eventLong != 1)
    return;

  SERIAL_DEBUG.printf("  BTN%i: long press\n\r", iButton);
  writeSwitchOutput(mParams.outputLong, mButtonParams[iButton].outputLong, BTN_KoBTNOutput2, BTN_KoBTNOutput2Status);
}
void VirtualButton::eventExtraLongPress(bool iButton)
{
  if (mParams.eventExtraLong != 1)
    return;

  SERIAL_DEBUG.printf("  BTN%i: extra long press\n\r", iButton);
  writeSwitchOutput(mParams.outputExtraLong, mButtonParams[iButton].outputExtraLong, BTN_KoBTNOutput3, BTN_KoBTNOutput3Status);
}
void VirtualButton::eventShortRelease(bool iButton)
{
  if (mParams.eventShort != 0)
    return;

  SERIAL_DEBUG.printf("  BTN%i: short release\n\r", iButton);
  writeSwitchOutput(mParams.outputShort, mButtonParams[iButton].outputShort, BTN_KoBTNOutput1, BTN_KoBTNOutput1Status);
}
void VirtualButton::eventLongRelease(bool iButton)
{
  if (mParams.eventLong != 0)
    return;

  SERIAL_DEBUG.printf("  BTN%i: long release\n\r", iButton);
  writeSwitchOutput(mParams.outputLong, mButtonParams[iButton].outputLong, BTN_KoBTNOutput2, BTN_KoBTNOutput2Status);
}
void VirtualButton::eventExtraLongRelease(bool iButton)
{
  if (mParams.eventExtraLong != 0)
    return;

  SERIAL_DEBUG.printf("  BTN%i: extra long release\n\r", iButton);
  writeSwitchOutput(mParams.outputExtraLong, mButtonParams[iButton].outputExtraLong, BTN_KoBTNOutput3, BTN_KoBTNOutput3Status);
}

void VirtualButton::writeSwitchOutput(uint8_t iOutput, uint8_t iValue, uint8_t iKoOutput, uint8_t iKoStatus)
{
  SERIAL_DEBUG.printf("  BTN WRITE %i/%i/%i/%i\n\r", iOutput, iValue, iKoOutput, iKoStatus);
  bool lValueBool = true;

  switch (iOutput)
  {
  case 1:
    // DPT1

    // disabled
    if (iValue == 0)
      return;

    // default true

    // true
    if (iValue == 1)
      lValueBool = false;

    // toggle
    if (iValue == 3)
    {
      lValueBool = !(bool)getKo(iKoStatus)->value(getDPT(VAL_DPT_1));
    }

    getKo(iKoOutput)->value(lValueBool, getDPT(VAL_DPT_1));
    break;

  case 4:
  case 6:
    // DPT5 & DPT17
    getKo(iKoOutput)->value((uint8_t)iValue, getDPT(VAL_DPT_5));
    break;

  case 5:
    // DPT5001
    getKo(iKoOutput)->value((uint8_t)iValue, getDPT(VAL_DPT_5001));
    break;
  }
}