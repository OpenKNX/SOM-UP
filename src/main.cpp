#include <OpenKNX.h>
#include "SoundModule.h"
#include "hardware.h"
#include "HardwareDevices.h"

void appSetup();
void appLoop();

void setup()
{
  Serial1.setRX(KNX_UART_RX_PIN);
  Serial1.setTX(KNX_UART_TX_PIN);
  SERIAL_DEBUG.begin(115200);

  pinMode(PROG_LED_PIN, OUTPUT);
  digitalWrite(PROG_LED_PIN, HIGH);
  delay(DEBUG_DELAY);
  digitalWrite(PROG_LED_PIN, LOW);

  Serial2.setRX(PLAYER_UART_RX_PIN);
  Serial2.setTX(PLAYER_UART_TX_PIN);

  SERIAL_DEBUG.println("Startup called...");
  ArduinoPlatform::SerialDebug = &SERIAL_DEBUG;

#ifdef INFO_LED_PIN
  pinMode(INFO_LED_PIN, OUTPUT);
  ledInfo(true);
#endif

  const uint8_t firmwareRevision = 0;
  OpenKNX::knxRead(MAIN_OpenKnxId, MAIN_ApplicationNumber, MAIN_ApplicationVersion, firmwareRevision);

  // pin or GPIO the programming led is connected to. Default is LED_BUILDIN
  knx.ledPin(PROG_LED_PIN);
  // is the led active on HIGH or low? Default is LOW
  knx.ledPinActiveOn(PROG_LED_PIN_ACTIVE_ON);
  // pin or GPIO programming button is connected to. Default is 0
  knx.buttonPin(PROG_BUTTON_PIN);
  // Is the interrup created in RISING or FALLING signal? Default is RISING
  // knx.buttonPinInterruptOn(PROG_BUTTON_PIN_INTERRUPT_ON);

  appSetup();

  // start the framework
  knx.start();
  ledInfo(false);
}

void loop()
{
  // don't delay here to much. Otherwise you might lose packages or mess up the timing with ETS
  knx.loop();
  appLoop();
}
