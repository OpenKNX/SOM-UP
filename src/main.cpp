#include "Logic.h"
#include "OpenKNX.h"
#include "SmartMF.h"
#include "SoundBinaryInputModule.h"
#include "SoundModule.h"
#include "UpdaterModule.h"
#include "VirtualButtonModule.h"

void setup()
{
    const uint8_t firmwareRevision = 1;
    openknx.init(firmwareRevision);
    smartmf.init();

    openknx.addModule(1, new Logic());
    openknx.addModule(2, new SoundModule());
    openknx.addModule(3, new VirtualButtonModule());
    openknx.addModule(4, new SoundBinaryInputModule());
    openknx.addModule(9, new UpdaterModule());
    openknx.setup();

    // OpenKNX::Flash::RP2040 test = OpenKNX::Flash::RP2040(OPENKNX_FLASH_OFFSET, OPENKNX_FLASH_SIZE, "Default"); // 1593344 +  65536
    // test.eraseSector(0);
    // uint32_t start = millis();
    // test.write(0, 0xFD, 64); // FD F9 F8 F0 E0
    // test.commit();
    // logInfo("Speed", "Time: %i ms", millis() - start);
    // test.printBaseInfo();
}

void loop()
{
    openknx.loop();
}