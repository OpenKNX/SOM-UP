#include "Helper.h"
#include "SoundControl.h"

SoundControl soundControl;

void processInputKoCallback(GroupObject &iKo)
{
  soundControl.processInputKo(iKo);
}

void appLoop()
{
  soundControl.loop();
}

void appSetup()
{
  if (knx.configured())
  {
    if (GroupObject::classCallback() == 0)
      GroupObject::classCallback(processInputKoCallback);

    soundControl.setup();
  }
}