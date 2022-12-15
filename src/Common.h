#include "KnxHelper.h"
#include "knxprod.h"
#include "Helper.h" // TODO: Hier ist das delayChecks drinne (Logicmodul)

class Common
{

private:
  uint32_t mStartupDelay;
  uint32_t mHeartbeatDelay;

public:
  Common();
  ~Common();

  bool setup();
  bool loop();
  bool processStartupDelay();
  void processHeartbeat();
  // void addTest(void (*callback)(int));
  // int *testArray[20];
};