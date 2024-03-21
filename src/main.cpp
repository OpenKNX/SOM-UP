#include "FileTransferModule.h"
#include "Logic.h"
#include "OpenKNX.h"
#include "SmartMF.h"
#include "SoundBinaryInputModule.h"
#include "SoundModule.h"
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"

void __time_critical_func(processKnxRxISR)()
{
    uart_get_hw(uart0)->icr = UART_UARTICR_RTIC_BITS | UART_UARTICR_RXIC_BITS;
    knx.bau().getDataLinkLayer()->processRxISR();
}

void setup()
{
    const uint8_t firmwareRevision = 2;
    openknx.init(firmwareRevision);
    smartmf.init();
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxSoundModule);
    openknx.addModule(4, openknxSoundBinaryInputModule);
    openknx.addModule(3, openknxVirtualButtonModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);
    openknx.setup();
    
    irq_set_exclusive_handler(KNX_DMA_UART_IRQ, processKnxRxISR);
    irq_set_enabled(KNX_DMA_UART_IRQ, true);
    uart_set_irq_enables(KNX_DMA_UART, true, false);
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