#include "Helper.h"
#include "OpenKNX/Common.h"
#include "OpenKNX/Module.h"
#include "Logic.h"
#include "VirtualButton.h"
#include "SoundControl.h"
#include "SoundBinaryInput.h"
#include "VirtualButtonControl.h"

SoundBinaryInput gSoundBinaryInput;
VirtualButtonControl gVirtualButtonControl;

SoundControl gSoundControl;
Logic gLogic;
// OpenKNX::Common gCommon;

void processReadRequests()
{
  // this method is called after startup delay and executes read requests, which should just happen once after startup
  static bool sCalledProcessReadRequests = false;
  if (!sCalledProcessReadRequests)
  {
    sCalledProcessReadRequests = true;
  }
  gLogic.processReadRequests();
}

bool processDiagnoseCommand()
{
  char *lBuffer = gLogic.getDiagnoseBuffer();
  bool lOutput = false;
  if (lBuffer[0] == 'v')
  {
    // Command v: retrun fimware version, do not forward this to logic,
    // because it means firmware version of the outermost module
    // sprintf(lBuffer, "VER [%d] %d.%d", cFirmwareMajor, cFirmwareMinor, cFirmwareRevision);
    lOutput = true;
  }
  else
  {
    // let's check other modules for this command
    // lOutput = gPresence.processDiagnoseCommand(lBuffer);
    if (!lOutput)
      lOutput = gLogic.processDiagnoseCommand();
  }
  return lOutput;
}

void processDiagnoseCommand(GroupObject &iKo)
{
  // this method is called as soon as iKo is changed
  // an external change is expected
  // because this iKo also is changed within this method,
  // the method is called again. This might result in
  // an endless loop. This is prevented by the isCalled pattern.
  static bool sIsCalledProcessDiagnoseCommand = false;
  if (!sIsCalledProcessDiagnoseCommand)
  {
    sIsCalledProcessDiagnoseCommand = true;
    // diagnose is interactive and reacts on commands
    gLogic.initDiagnose(iKo);
    if (processDiagnoseCommand())
      gLogic.outputDiagnose(iKo);
    sIsCalledProcessDiagnoseCommand = false;
  }
};

void processInputKoCallback(GroupObject &iKo)
{
  uint16_t lAsap = iKo.asap();
  switch (lAsap)
  {
  case LOG_KoDiagnose:
    processDiagnoseCommand(iKo);
    break;

  case LOG_KoHeartbeat:
    SERIAL_DEBUG.println("HA");
    gLogic.debug();
    break;

  default:
    OpenKNX::Common::processInputKo(iKo);
    //gSoundControl.processInputKo(iKo);
    gLogic.processInputKo(iKo);
    gVirtualButtonControl.processInputKo(iKo);
  }
}

void appLoop()
{
  if (!OpenKNX::Common::loop())
    return;

  processReadRequests();
  //gSoundBinaryInput.loop();
  gVirtualButtonControl.loop();
  //gSoundControl.loop();
  gLogic.loop();
}

void appSetup()
{
  OpenKNX::Common::addModule(&gSoundControl);
  OpenKNX::Common::addModule(&gSoundBinaryInput);

  if (!OpenKNX::Common::setup())
    return;

  if (GroupObject::classCallback() == 0)
   GroupObject::classCallback(processInputKoCallback);

  //gSoundControl.setup();
  //gSoundBinaryInput.setup();
  gVirtualButtonControl.setup();
  gLogic.setup(true);
  
  OpenKNX::Common::registerCallbacks();
}
