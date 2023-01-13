#include "hardware.h"
#include "HardwareDevices.h"

#include "SoundControl.h"
#include "SoundBinaryInput.h"
#include "VirtualButtonControl.h"

#include "knx.h"
#include "OpenKNX.h"

void setup()
{
  const uint8_t firmwareRevision = 0;
  openknx.init(firmwareRevision);

  openknx.addModule(new SoundBinaryInput());
  openknx.addModule(new VirtualButtonControl());
  openknx.addModule(new SoundControl());

  openknx.setup();
}

void loop()
{
  openknx.loop();
}
