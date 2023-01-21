#include "BinaryInputChannel.h"
#include "OpenKNX/Module.h"
#include "hardware.h"

class SoundBinaryInputModule : public OpenKNX::Module
{

  public:
    SoundBinaryInputModule();

    virtual const char *name() override;
    void loop();
    void setup();

  private:
    void processHardwareInputs();

    uint32_t _lastHardwareQuery = 0;

    BinaryInputChannel *_binaryInputChannels[BI_ChannelCount] = {
        new BinaryInputChannel(0),
        new BinaryInputChannel(1),
        new BinaryInputChannel(2),
        new BinaryInputChannel(3)};
};