#include "OpenKNX/Module.h"

namespace OpenKNX
{
  uint32_t Module::calcParamIndex(uint16_t iParamIndex)
  {
    return iParamIndex + (mChannelIndex * mChannelParamBlockSize) + mChannelParamOffset;
  }

  uint16_t Module::calcKoNumber(uint8_t iKoIndex)
  {
    return iKoIndex + (mChannelIndex * mChannelParamKoBlockSize) + mChannelParamKoOffset;
  }

  int8_t Module::calcKoIndex(uint16_t iKoNumber)
  {
    int16_t lResult = (iKoNumber - mChannelParamKoOffset);
    // check if channel is valid
    if ((int8_t)(lResult / mChannelParamKoBlockSize) == mChannelIndex)
      lResult = lResult % mChannelParamKoBlockSize;
    else
      lResult = -1;
    return (int8_t)lResult;
  }

  GroupObject *Module::getKo(uint8_t iKoIndex)
  {
    return &knx.getGroupObject(calcKoNumber(iKoIndex));
  }

  void Module::loop() {}
  void Module::setup() {}
}
