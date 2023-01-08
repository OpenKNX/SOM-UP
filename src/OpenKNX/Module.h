#pragma once
#include "KnxHelper.h"
#include "knxprod.h"
#include "Helper.h" // TODO: Hier ist das delayChecks drinne (Logicmodul)
#include <cstdio>
#include <functional>

namespace OpenKNX
{
  class Module
  {
  protected:
    uint8_t mChannelIndex = 0;
    uint16_t mChannelParamBlockSize = 0;
    uint16_t mChannelParamOffset = 0;
    uint16_t mChannelParamKoBlockSize = 0;
    uint16_t mChannelParamKoOffset = 0;

    uint32_t calcParamIndex(uint16_t iParamIndex);
    uint16_t calcKoNumber(uint8_t iKoIndex);
    int8_t calcKoIndex(uint16_t iKoNumber);
    GroupObject *getKo(uint8_t iKoIndex);

  public:
    virtual void loop();
    virtual void setup();
    virtual void processInputKo(GroupObject &iKo);
    virtual void onSafePinInterruptHandler();
  };
}