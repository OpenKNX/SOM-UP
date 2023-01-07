#include "OpenKNX/Common.h"

namespace OpenKNX
{
  Common::Common() {}
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

    processLoop();
    return true;
  }

  void Common::callLoop()
  {
    //  SERIAL_DEBUG.println("CALLBACK");
  }

  bool Common::setup()
  {
    if (!knx.configured())
      return false;

    mStartupDelay = millis();
    mHeartbeatDelay = 0;

    for (uint8_t i = 0; i < MAX_LOOP_CALLBACKS; i++)
    {
      Common::addLoop([this]() -> void
                      { this->callLoop(); });
    }

    return true;
  }

  void Common::addLoop(std::function<void()> callback)
  {
    sLoopCallbackCount++;
    sLoopCallback[sLoopCallbackCount - 1] = callback;
  }

  void Common::processLoop()
  {
    if (!sLoopCallbackCount)
      return;

    for (uint8_t i = 1; i <= sLoopCallbackCount; i++)
    {
      sLoopCallback[i - 1]();
    }
  }
}