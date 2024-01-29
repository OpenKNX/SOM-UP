#include "FileTransferModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "SmartMF.h"
#include "SoundBinaryInputModule.h"
#include "SoundModule.h"
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    smartmf.init();
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxSoundModule);
    openknx.addModule(4, openknxSoundBinaryInputModule);
    openknx.addModule(3, openknxVirtualButtonModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);
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