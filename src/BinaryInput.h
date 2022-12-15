#pragma once
#include "knx.h"
#include "Helper.h"
#include "KnxHelper.h"
#include "knxprod.h"
#include "hardware.h"

class BinaryInput
{

protected:
  uint32_t calcParamIndex(uint16_t iParamIndex);
  uint16_t calcKoNumber(uint8_t iKoIndex);
  int8_t calcKoIndex(uint16_t iKoNumber);
  GroupObject *getKo(uint8_t iKoIndex);
  bool debounced(bool iCurrentState);
  void processInput();
  void processPeriodicSend();
  bool checkQueryTime();
  void sendState();

  uint8_t mParamActive;
  bool mParamMode;
  uint8_t mParamDebouncing;
  uint32_t mParamPeriodic;
  uint8_t mParamPulsing;

  uint8_t mIndex = 0;
  uint8_t mInputPin = 0;
  int8_t mPulsePin = 0;

  int8_t mCurrentState = -1;
  int8_t mLastButtonState = -1;
  uint32_t mLastDebounceTime = 0;
  uint32_t mLastQueryTime = 0;
  uint32_t mLastPeriodicSend = 0;

public:
  BinaryInput(uint8_t iIndex, uint8_t iInputPin, int8_t iPulsePin);
  ~BinaryInput();
  
  void setup();
  void loop();
  void processInputKo(GroupObject &iKo);
  virtual bool queryHardwareInput();
};
