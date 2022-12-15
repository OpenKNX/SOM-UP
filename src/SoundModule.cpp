#include "Helper.h"
#include "Common.h"
#include "Logic.h"
#include "BinaryInput.h"
#include "SoundControl.h"

SoundControl gSoundControl;
Logic gLogic;
Common gCommon;
BinaryInput gBinaryInputA(0, BINARY_INPUT_A_PIN, BINARY_INPUT_PULSE);
BinaryInput gBinaryInputB(1, BINARY_INPUT_B_PIN, BINARY_INPUT_PULSE);
BinaryInput gBinaryInputC(2, BINARY_INPUT_C_PIN, BINARY_INPUT_PULSE);
BinaryInput gBinaryInputD(3, BINARY_INPUT_D_PIN, BINARY_INPUT_PULSE);

void ProcessReadRequests()
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

void ProcessDiagnoseCommand(GroupObject &iKo)
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
  uint16_t asap = iKo.asap();
  switch (asap)
  {
  case LOG_KoDiagnose:
    ProcessDiagnoseCommand(iKo);
    break;

  case LOG_KoHeartbeat:
    SERIAL_DEBUG.println("HA");
    gLogic.debug();
    break;

  default:
    // gCommon.processInputKo(iKo);
    gSoundControl.processInputKo(iKo);
    gLogic.processInputKo(iKo);

  }
}

bool pressed = false;
void appLoop()
{
  if (!gCommon.loop())
    return;

  ProcessReadRequests();
  gSoundControl.loop();
  gLogic.loop();
  gBinaryInputA.loop();
  gBinaryInputB.loop();
  gBinaryInputC.loop();
  gBinaryInputD.loop();
}

void appSetup()
{
  if (!gCommon.setup())
    return;

  if (GroupObject::classCallback() == 0)
    GroupObject::classCallback(processInputKoCallback);

  gBinaryInputA.setup();
  gBinaryInputB.setup();
  gBinaryInputC.setup();
  gBinaryInputD.setup();
  gSoundControl.setup();
  gLogic.setup(true);
}