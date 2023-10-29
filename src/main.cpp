#include "FileTransferModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "SmartMF.h"
#include "SoundBinaryInputModule.h"
#include "SoundModule.h"
#include "VirtualButtonModule.h"

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    smartmf.init();

    openknx.addModule(1, new Logic());
    openknx.addModule(2, new SoundModule());
    openknx.addModule(3, new VirtualButtonModule());
    openknx.addModule(4, new SoundBinaryInputModule());
    openknx.addModule(9, new FileTransferModule());
    openknx.setup();
}

void loop()
{
    openknx.loop();
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();
}
#endif