#include "BinaryInput.h"
#include "hardware.h"

class BinaryInputControl
{

public:
  BinaryInputControl();
  ~BinaryInputControl();

  void loop();
  void setup();

private:
  void processHardwareInputs();

  uint32_t mLastHardwareQuery = 0;

  BinaryInput *mBinaryInputs[BI_ChannelCount] = {
      new BinaryInput(0),
      new BinaryInput(1),
      new BinaryInput(2),
      new BinaryInput(3)};
};