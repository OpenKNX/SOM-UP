#include "FileTransferModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "SmartMF.h"
#include "SoundModule.h"
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"
#ifdef OPENKNX_BI_GPIO_COUNT
    #include "GpioBinaryInputModule.h"
#endif

void setup()
{
    openknx.init();
    smartmf.init();
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxSoundModule);
#ifdef OPENKNX_BI_GPIO_COUNT
    openknx.addModule(4, openknxGpioBinaryInputModule);
#else
    openknx.unsupportedEtsModule(ETS_ModuleId_BI);
#endif
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