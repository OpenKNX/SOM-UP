#pragma once
#define BINARY_INPUT_PULSE_PAUSE_TIME 5  // MS
#define BINARY_INPUT_PULSE_WAIT_TIME 250 // US

#ifdef BOARD_MASIFI_SENSOR_BREAKOUT
    // #define OPENKNX_RECOVERY_ON LOW
    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define INFO1_LED_PIN 3
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 22
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define PLAYER_UART_RX_PIN 9
    #define PLAYER_UART_TX_PIN 8
    #define PLAYER_I2S_BCLK_PIN 8
    #define PLAYER_I2S_DATA_PIN 20
    #define BINARY_INPUT_PULSE_PIN 5
    #define BINARY_INPUT_A_PIN 2
    #define BINARY_INPUT_B_PIN 4
    #define BINARY_INPUT_C_PIN 6
    #define BINARY_INPUT_D_PIN 7
    #define HARDWARE_NAME "MASIFI-SENSOR-BREAKOUT"
    #define SmartMF_HardwareVariant_PIN 26
    #define SmartMF_HardwareRevision_PIN1 10
    #define SmartMF_HardwareRevision_PIN2 11
    #define SmartMF_HardwareRevision_PIN3 12
#endif

#ifdef BOARD_SOM_UP
    #define PROG_LED_PIN 2
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define INFO1_LED_PIN 29
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 13
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define PLAYER_UART_RX_PIN 9
    #define PLAYER_UART_TX_PIN 8
    #define PLAYER_I2S_BCLK_PIN 8
    #define PLAYER_I2S_DATA_PIN 20
    #define PLAYER_POWER_PIN 3
    #define BINARY_INPUT_PULSE_PIN 14
    #define BINARY_INPUT_A_PIN 4
    #define BINARY_INPUT_B_PIN 5
    #define BINARY_INPUT_C_PIN 19
    #define BINARY_INPUT_D_PIN 18
    #define HARDWARE_NAME "SOM-UP"

    #define SmartMF_HardwareRevision_PIN1 10
    #define SmartMF_HardwareRevision_PIN2 11
    #define SmartMF_HardwareRevision_PIN3 12
#endif