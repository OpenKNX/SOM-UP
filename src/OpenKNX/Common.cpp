#include "OpenKNX/Common.h"
#include "hardware.h"

OpenKNX::Modules OpenKNX::Common::modules;
#ifdef LOG_StartupDelayBase
uint32_t OpenKNX::Common::startupDelay = 0;
#endif
#ifdef LOG_HeartbeatDelayBase
uint32_t OpenKNX::Common::heartbeatDelay = 0;
#endif
bool OpenKNX::Common::calledSaveInterrupt = false;

namespace OpenKNX
{

#ifdef LOG_StartupDelayBase
  bool Common::processStartupDelay()
  {
    return !delayCheck(startupDelay, getDelayPattern(LOG_StartupDelayBase));
  }
#endif

#ifdef LOG_HeartbeatDelayBase
  void Common::processHeartbeat()
  {
    // the first heartbeat is send directly after startup delay of the device
    if (heartbeatDelay == 0 || delayCheck(heartbeatDelay, getDelayPattern(LOG_HeartbeatDelayBase)))
    {
      // we waited enough, let's send a heartbeat signal
      knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
      heartbeatDelay = millis();
    }
  }
#endif

  bool Common::loop()
  {
    if (calledSaveInterrupt)
    {
      SERIAL_DEBUG.println("execute save handling");
      for (uint8_t i = 1; i <= modules.count; i++)
      {
        modules.list[i - 1]->onSafePinInterruptHandler();
      }
      // TODO SaveToFlash

      // Then reboot
      watchdog_reboot(0, 0, 0);
    }

    if (!knx.configured())
      return false;

      // Handle Startup delay
#ifdef LOG_StartupDelayBase
    if (processStartupDelay())
      return false;
#endif

      // Handle heartbeat delay
#ifdef LOG_HeartbeatDelayBase
    processHeartbeat();
#endif

    for (uint8_t i = 1; i <= modules.count; i++)
    {
      modules.list[i - 1]->loop();
    }

    return true;
  }

  bool Common::setup()
  {
    if (!knx.configured())
      return false;

    startupDelay = millis();
    heartbeatDelay = 0;

    for (uint8_t i = 1; i <= modules.count; i++)
    {
      modules.list[i - 1]->setup();
    }

    return true;
  }

  void Common::onSafePinInterruptHandler()
  {
    SERIAL_DEBUG.println("hook onSafePinInterruptHandler");
    calledSaveInterrupt = true;
  }

  void Common::onBeforeRestartHandler()
  {
    SERIAL_DEBUG.println("hook onBeforeRestartHandler");
  }

  void Common::onBeforeTablesUnloadHandler()
  {
    SERIAL_DEBUG.println("hook onBeforeTablesUnloadHandler");
  }

  void Common::processInputKo(GroupObject &iKo)
  {
    //SERIAL_DEBUG.printf("hook onInputKo %i\n\r", iKo.asap());
    for (uint8_t i = 1; i <= modules.count; i++)
    {
      modules.list[i - 1]->processInputKo(iKo);
    }
  }

  void Common::registerCallbacks()
  {
    knx.beforeRestartCallback(onBeforeRestartHandler);
    //GroupObject::classCallback(processInputKo);
    TableObject::beforeTablesUnloadCallback(onBeforeTablesUnloadHandler);
#ifdef SAVE_INTERRUPT_PIN
    // we need to do this as late as possible, tried in constructor, but this doesn't work on RP2040
    pinMode(SAVE_INTERRUPT_PIN, INPUT);
    SERIAL_DEBUG.printf("SAVE %i\n\r", digitalPinToInterrupt(SAVE_INTERRUPT_PIN));
    attachInterrupt(digitalPinToInterrupt(SAVE_INTERRUPT_PIN), onSafePinInterruptHandler, FALLING);
#endif
  }

  void Common::addModule(Module *module)
  {
    modules.count++;
    modules.list[modules.count - 1] = module;
  }

}