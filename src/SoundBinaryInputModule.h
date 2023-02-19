#include "BinaryInputChannel.h"
#include "OpenKNX/Module.h"
#include "hardware.h"

class SoundBinaryInputModule : public OpenKNX::Module
{

  public:
    const std::string name() override;
    const std::string version() override;
    void loop() override;
    void setup() override;

  private:
    void processHardwareInputs();

    uint32_t _lastHardwareQuery = 0;

    BinaryInputChannel *_channels[BI_ChannelCount] = {
        new BinaryInputChannel(0),
        new BinaryInputChannel(1),
        new BinaryInputChannel(2),
        new BinaryInputChannel(3)};
};