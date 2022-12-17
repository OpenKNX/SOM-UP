#pragma once
#include "knx.h"
#include "Helper.h"
#include "KnxHelper.h"
#include "knxprod.h"
#include "hardware.h"

#define BTN_MaxMuliClicks 3
#define BTN_MuliClickTime 500
#define BTN_LongPressTime 1000
#define BTN_ExtraLongPressTime 2500

struct VirtualButtonParams
{
  uint8_t outputShort;
  uint8_t outputLong;
  uint8_t outputExtraLong;
};

struct VirtualButtonGlobalParams
{
  uint8_t mode = 0;
  uint8_t lock = 0;
  uint8_t outputShort = 0;
  uint8_t outputLong = 0;
  uint8_t outputExtraLong = 0;
  bool eventShort = false;
  bool eventLong = false;
  bool eventExtraLong = false;
};

struct VirtualButtonState
{
  bool press = false;
  bool pressLong = false;
  bool pressExtraLong = false;
  uint32_t pressStart = 0;
  uint32_t multiClickTimer = 0;
  int8_t multiClicks = 0;
};


class VirtualButton
{

private:
  uint32_t calcParamIndex(uint16_t iParamIndex);
  uint16_t calcKoNumber(uint8_t iKoIndex);
  int8_t calcKoIndex(uint16_t iKoNumber);
  GroupObject *getKo(uint8_t iKoIndex);

  void processInputKoInput(GroupObject &iKo, bool iButton);
  void processInputKoLock(GroupObject &iKo);
  void processPress(bool iButton);
  void processRelease(bool iButton);
  void processPressAndHold(bool iButton);
  void processMultiClick();
  void eventMultiClick(uint8_t iClicks);
  void eventShortPress(bool iButton);
  void eventLongPress(bool iButton);
  void eventExtraLongPress(bool iButton);
  void eventShortRelease(bool iButton);
  void eventLongRelease(bool iButton);
  void eventExtraLongRelease(bool iButton);
  void writeSwitchOutput(uint8_t iOutput, uint8_t iValue, uint8_t iKoOutput, uint8_t iKoStatus);

  uint8_t mIndex = 0;

  VirtualButtonState mButtonState[2] = {
    VirtualButtonState(),
    VirtualButtonState()
  };
  VirtualButtonParams mButtonParams[2] = {
    VirtualButtonParams(),
    VirtualButtonParams()
  };
  VirtualButtonGlobalParams mParams;

public:
  VirtualButton(uint8_t iIndex);
  ~VirtualButton();

  void setup();
  void loop();
  void processInputKo(GroupObject &iKo);
};