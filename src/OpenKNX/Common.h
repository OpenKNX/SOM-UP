#include "KnxHelper.h"
#include "knxprod.h"
#include "Helper.h" // TODO: Hier ist das delayChecks drinne (Logicmodul)
#include <cstdio>
#include <functional>

#define MAX_LOOP_CALLBACKS 20

namespace OpenKNX
{
  class Common
  {

  private:
    uint32_t mStartupDelay;
    uint32_t mHeartbeatDelay;

    std::function<void()> sLoopCallback[MAX_LOOP_CALLBACKS];
    uint16_t sLoopCallbackCount = 0;

  public:
    Common();
    ~Common();

    bool setup();
    bool loop();

#ifdef LOG_StartupDelayBase
    bool processStartupDelay();
#endif
#ifdef LOG_HeartbeatDelayBase
    void processHeartbeat();
#endif
    void addLoop(std::function<void()> callback);
    void processLoop();
    void callLoop();
  };
}