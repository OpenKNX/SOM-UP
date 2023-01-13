#include "KnxHelper.h"
#include "knxprod.h"
#include "Helper.h" // TODO: Hier ist das delayChecks drinne (Logicmodul)
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include "OpenKNX/Module.h"

#define MAX_MODULES 9

namespace OpenKNX
{
  struct Modules
  {
    uint8_t count = 0;
    Module *list[MAX_MODULES];
  };

  class Common
  {
  public:
    static bool calledAfterSetup;
    static bool calledSaveInterrupt;
    static Modules modules;

    static bool setup();
    static bool loop();
    static void addModule(Module *module);
    static void registerCallbacks();
    static void onSafePinInterruptHandler();
    static void onBeforeRestartHandler();
    static void onBeforeTablesUnloadHandler();
    static void processInputKo(GroupObject &iKo);
    static void log(const char* iModuleName, const char* iMessage);
    static void processSerialInput();


#ifdef LOG_StartupDelayBase
    static uint32_t startupDelay;
    static bool processStartupDelay();
#endif
#ifdef LOG_HeartbeatDelayBase
    static uint32_t heartbeatDelay;
    static void processHeartbeat();
#endif
  };
}