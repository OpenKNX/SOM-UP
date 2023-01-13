#include "VirtualButton.h"
#include "hardware.h"

class VirtualButtonControl : public OpenKNX::Module
{

public:
  VirtualButtonControl();
  ~VirtualButtonControl();

  void loop();
  void setup();
  void processInputKo(GroupObject &iKo);

private:
  void processHardwareInputs();

  uint32_t mLastHardwareQuery = 0;

  
  VirtualButton *mVirtualButtons[BTN_ChannelCount];
};