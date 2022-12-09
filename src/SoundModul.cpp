#include "Helper.h"
#include "SoundControl.h"
#include "Logic.h"
#include "KnxHelper.h"

struct sRuntimeInfo
{
  uint32_t startupDelay;
  uint32_t heartbeatDelay;
};

sRuntimeInfo gRuntimeData;

SoundControl soundControl;
Logic gLogic;

void ProcessHeartbeat()
{
  // the first heartbeat is send directly after startup delay of the device
  if (gRuntimeData.heartbeatDelay == 0 || delayCheck(gRuntimeData.heartbeatDelay, getDelayPattern(LOG_HeartbeatDelayBase)))
  {
    // we waited enough, let's send a heartbeat signal
    knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
    gRuntimeData.heartbeatDelay = millis();
    // debug entry point
    // gPresence.debug();
    gLogic.debug();
  }
}

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

// true solgange der Start des gesamten Moduls verzögert werden soll
bool startupDelay()
{
  return !delayCheck(gRuntimeData.startupDelay, getDelayPattern(LOG_StartupDelayBase, true));
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
  if (iKo.asap() == LOG_KoDiagnose)
  {
    ProcessDiagnoseCommand(iKo);
  }
  else
  {
    soundControl.processInputKo(iKo);
    gLogic.processInputKo(iKo);
  }
}

void appLoop()
{
  ProcessHeartbeat();
  ProcessReadRequests();
  soundControl.loop();
  gLogic.loop();
}

void appSetup()
{
  if (knx.configured())
  {
    if (GroupObject::classCallback() == 0)
      GroupObject::classCallback(processInputKoCallback);

    gRuntimeData.startupDelay = millis();
    gRuntimeData.heartbeatDelay = 0;
    soundControl.setup();
    gLogic.setup(false);
  }
}