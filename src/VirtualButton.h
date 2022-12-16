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

struct VirtualButtonOutputParams
{
  uint8_t dpt1 = 0;
  uint8_t dpt5 = 0;
  uint8_t dpt5001 = 0;
  uint8_t dpt17 = 0;
};

struct VirtualButtonParams
{
  struct VirtualButtonOutputParams outputShort;
  struct VirtualButtonOutputParams outputLong;
  struct VirtualButtonOutputParams outputExtraLong;
};

struct VirtualButtonGlobalParams
{
  uint8_t mode = 0;
  uint8_t lock = 0;
  uint8_t outputShort = 0;
  uint8_t outputLong = 0;
  uint8_t outputExtraLong = 0;
};

struct VirtualButtonState
{
  bool shortPress = false;
  bool longPress = false;
  bool extraLongPress = false;
  uint32_t pressedStart = 0;
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
  void processMultiClickReset();
  void multiClick(uint8_t iClicks);

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