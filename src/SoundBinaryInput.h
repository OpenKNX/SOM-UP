#include "BinaryInput.h"
#include "hardware.h"
#include "OpenKNX/Module.h"

class SoundBinaryInput : public OpenKNX::Module
{

public:
  SoundBinaryInput();
  ~SoundBinaryInput();

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