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
  // Params
  mParamMode = knx.paramByte(calcParamIndex(BTN_BTNMode));
  // mParamMode = (knx.paramByte(calcParamIndex(BTN_BTNMode)) & BTN_BTNModeMask) >> BTN_BTNModeShift;

  // Debug
  SERIAL_DEBUG.printf("BTN %i mParamMode: %i\n\r", mIndex, mParamMode);
}

void VirtualButton::loop()
{
  processPress(0);
  processPress(1);
  processMultiClickReset(0);
}

void VirtualButton::processInputKo(GroupObject &iKo)
{
  if (mParamMode == 0)
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

void VirtualButton::processPress(bool iButton)
{
  if (!mButton[iButton]->shortPress)
    return;

  if (!mButton[iButton]->longPress && (millis() - mButton[iButton]->pressedStart) > 1000)
  {
    SERIAL_DEBUG.printf(" - long press\n\r");
    mButton[iButton]->longPress = true;
  }

  if (!mButton[iButton]->extraLongPress && (millis() - mButton[iButton]->pressedStart) > 2500)
  {
    SERIAL_DEBUG.printf(" - extra long press\n\r");
    mButton[iButton]->extraLongPress = true;
  }
}

void VirtualButton::processInputKoInput(GroupObject &iKo, bool iButton)
{
  bool lNewPress = iKo.value(getDPT(VAL_DPT_1));
  bool lLastPress = mButton[iButton]->shortPress;
  //SERIAL_DEBUG.printf("BTN::processInputKoInput %i/%i: %i -> %i\n\r", mIndex, iButton, lLastPress, lNewPress);

  if (lNewPress)
  {
    SERIAL_DEBUG.printf(" - press\n\r");
    mButton[iButton]->pressedStart = millis();
  }

  if (!lNewPress && mButton[iButton]->shortPress)
  {
    if (mButton[iButton]->extraLongPress)
    {
      mButton[iButton]->multiClicks = 0;
      mButton[iButton]->multiClickTimer = 0;
      SERIAL_DEBUG.printf(" - extra long release\n\r");
    }
    else if (mButton[iButton]->longPress)
    {
      mButton[iButton]->multiClicks = 0;
      mButton[iButton]->multiClickTimer = 0;
      SERIAL_DEBUG.printf(" - long release\n\r");
    }
    else
    {
      SERIAL_DEBUG.printf(" - release\n\r");

      // Allow multiclick only for first button
      if (iButton == 0) {

        processMultiClickReset(0);

        // Check for multiclick
        if (
            mButton[iButton]->multiClickTimer == 0 ||
            (millis() - mButton[iButton]->multiClickTimer) <= 600)
        {
          mButton[iButton]->multiClicks += 1;
          mButton[iButton]->multiClickTimer = millis();
        }
      }

    }

    mButton[iButton]->shortPress = false;
    mButton[iButton]->longPress = false;
    mButton[iButton]->extraLongPress = false;
    mButton[iButton]->pressedStart = 0;
  }

  mButton[iButton]->shortPress = lNewPress;
}

void VirtualButton::processMultiClickReset(bool iButton)
{
  // multiclick: reset timer if expired
  if (
      mButton[iButton]->multiClickTimer > 0 &&
      (millis() - mButton[iButton]->multiClickTimer) > 600)
  {
    SERIAL_DEBUG.printf(" - multiclick: %i\n\r", mButton[iButton]->multiClicks);
    mButton[iButton]->multiClickTimer = 0;
    mButton[iButton]->multiClicks = 0;
  }
}

void VirtualButton::processInputKoLock(GroupObject &iKo)
{
  bool lValue = iKo.value(getDPT(VAL_DPT_1));
  //SERIAL_DEBUG.printf("BTN::processInputKoLock %i: %i\n\r", mIndex, lValue);
}
