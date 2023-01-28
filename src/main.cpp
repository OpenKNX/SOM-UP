#include "OpenKNX.h"
#include "SmartMF.h"
#include "Logic.h"
#include "SoundBinaryInputModule.h"
#include "SoundModule.h"
#include "VirtualButtonModule.h"

void setup()
{
    const uint8_t firmwareRevision = 1;
    openknx.init(firmwareRevision);
    smartmf.init();
    
    openknx.addModule(4, new SoundBinaryInputModule());
    openknx.addModule(3, new VirtualButtonModule());
    openknx.addModule(2, new SoundModule());
    openknx.addModule(1, new Logic());
    openknx.setup();
}

void loop()
{
    openknx.loop();
}
