#include "VirtualButtonControl.h"

VirtualButtonControl::VirtualButtonControl() {}
VirtualButtonControl::~VirtualButtonControl() {}

void VirtualButtonControl::setup()
{
  for (uint8_t i = 0; i < BTN_ChannelCount; i++)
  {
    mVirtualButtons[i] = new VirtualButton(i);
    mVirtualButtons[i]->setup();
  }
}

void VirtualButtonControl::loop()
{
  for (uint8_t i = 0; i < BTN_ChannelCount; i++)
    mVirtualButtons[i]->loop();
}

void VirtualButtonControl::processInputKo(GroupObject &iKo)
{
  for (uint8_t i = 0; i < BTN_ChannelCount; i++)
    mVirtualButtons[i]->processInputKo(iKo);
}
