#include "KnxHelper.h"
#include "knxprod.h"
#include "Helper.h" // TODO: Hier ist das delayChecks drinne (Logicmodul)
#include <cstdio>
#include <functional>
#include "OpenKNX/Module.h"

#define MAX_LOOP_CALLBACKS 20
#define MAX_MODULES 10

namespace OpenKNX
{
  class Common
  {

  private:
    uint32_t mStartupDelay;
    uint32_t mHeartbeatDelay;

    Module *mModules[MAX_MODULES];
    uint16_t mModulesCount = 0;

  public:
    Common();
    ~Common();

    static Common *sInstance;

    bool setup();
    bool loop();
    void registerCallbacks();

    static void onSafePinInterruptHandler();
    static void onBeforeRestartHandler();
    static void onBeforeTablesUnloadHandler();
    static void onInputKo(GroupObject &iKo);
    
    void _onSafePinInterruptHandler();
    void _onBeforeRestartHandler();
    void _onBeforeTablesUnloadHandler();
    void _onInputKo(GroupObject &iKo);

#ifdef LOG_StartupDelayBase
    bool processStartupDelay();
#endif
#ifdef LOG_HeartbeatDelayBase
    void processHeartbeat();
#endif

    void addModule(Module *iModule);
  };
}