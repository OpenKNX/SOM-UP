#include "OpenKNX/Common.h"

namespace OpenKNX
{

  Common *Common::sInstance = nullptr;

  Common::Common()
  {
    Common::sInstance = this;
  }
  Common::~Common() {}

#ifdef LOG_StartupDelayBase
  bool Common::processStartupDelay()
  {
    return !delayCheck(mStartupDelay, getDelayPattern(LOG_StartupDelayBase));
  }
#endif

#ifdef LOG_HeartbeatDelayBase
  void Common::processHeartbeat()
  {
    // the first heartbeat is send directly after startup delay of the device
    if (mHeartbeatDelay == 0 || delayCheck(mHeartbeatDelay, getDelayPattern(LOG_HeartbeatDelayBase)))
    {
      // we waited enough, let's send a heartbeat signal
      knx.getGroupObject(LOG_KoHeartbeat).value(true, getDPT(VAL_DPT_1));
      mHeartbeatDelay = millis();
    }
  }
#endif

  bool Common::loop()
  {
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

    for (uint8_t i = 1; i <= mModulesCount; i++)
    {
      mModules[i - 1]->loop();
    }

    return true;
  }

  bool Common::setup()
  {
    if (!knx.configured())
      return false;

    mStartupDelay = millis();
    mHeartbeatDelay = 0;

    for (uint8_t i = 1; i <= mModulesCount; i++)
    {
      mModules[i - 1]->setup();
    }

    return true;
  }

  void Common::onSafePinInterruptHandler()
  {
    sInstance->_onSafePinInterruptHandler();
  }

  void Common::_onSafePinInterruptHandler()
  {
    SERIAL_DEBUG.println("hook onSafePinInterruptHandler");
  }

  void Common::onBeforeRestartHandler()
  {
    sInstance->_onBeforeRestartHandler();
  }

  void Common::_onBeforeRestartHandler()
  {
    SERIAL_DEBUG.println("hook onBeforeRestartHandler");
  }

  void Common::onBeforeTablesUnloadHandler()
  {
    sInstance->_onBeforeTablesUnloadHandler();
  }

  void Common::_onBeforeTablesUnloadHandler()
  {
    SERIAL_DEBUG.println("hook onBeforeTablesUnloadHandler");
  }

  void Common::onInputKo(GroupObject &iKo)
  {
    sInstance->_onInputKo(iKo);
  }

  void Common::_onInputKo(GroupObject &iKo)
  {
    SERIAL_DEBUG.println("hook onInputKo");
    for (uint8_t i = 1; i <= mModulesCount; i++)
    {
      mModules[i - 1]->processInputKo(iKo);
    }
  }

  void Common::registerCallbacks()
  {
    // knx.beforeRestartCallback(onBeforeRestartHandler);
    // GroupObject::classCallback(processInputKoCallback);
    // TableObject::beforeTablesUnloadCallback(onBeforeTablesUnloadHandler);
#ifdef SAVE_INTERRUPT_PIN
    // we need to do this as late as possible, tried in constructor, but this doesn't work on RP2040
    // pinMode(SAVE_INTERRUPT_PIN, INPUT);
    // attachInterrupt(digitalPinToInterrupt(SAVE_INTERRUPT_PIN), onSafePinInterruptHandler, FALLING);
#endif
  }

  void Common::addModule(Module *iModule)
  {
    mModulesCount++;
    mModules[mModulesCount - 1] = iModule;
  }

}