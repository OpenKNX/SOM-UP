#pragma once
#include "knx.h"
#include "Helper.h"
#include "KnxHelper.h"
#include "knxprod.h"

class BinaryInput
{
  
private:
  uint32_t calcParamIndex(uint16_t paramIndex);
  uint16_t calcKoNumber(uint8_t koIndex);
  int8_t calcKoIndex(uint16_t koNumber);
  GroupObject *getKo(uint8_t koIndex);
  bool debounced(bool iCurrentState);
  void processInput();
  void processPeriodicSend();
  bool queryInput();
  bool checkQueryTime();
  void sendState();

  bool paramState;
  bool paramInvert;
  uint8_t paramDebouncing;
  uint32_t paramPeriodic;
  uint8_t paramPulsing;

  uint8_t mIndex = 0;
  uint8_t mInputPin = 0;
  int8_t mPulsePin = 0;

  int8_t mCurrentState = -1;
  int8_t mLastButtonState = -1;
  uint32_t mLastDebounceTime = 0;
  uint32_t mLastQueryTime = 0;
  uint32_t mLastPeriodicSend = 0;
public:
  BinaryInput(uint8_t iIndex, uint8_t iInputPin, int8_t iPulsePin = -1);
  ~BinaryInput();

  void setup();
  void loop();
  void processInputKo(GroupObject &iKO);
};