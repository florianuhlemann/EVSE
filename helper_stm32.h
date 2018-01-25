// HELPER_STM32 library: This library provides helper functions and definitions for STM32F0 chip.

// Type Definitions
#ifndef EVSEMODE_H
#define EVSEMODE_H
typedef enum { DISCONNECTED = 0, CONNECTED_NO_PWM = 1, CONNECTED = 2, CHARGING = 3, CHARGING_COOLED = 4, FAULT = 5 } CONTROLPILOT_STM32_EVSE_MODE;
#endif /* EVSEMODE_H */

// Function Declarations
void HELPER_STM32_initSystemClocks(void);
void HELPER_STM32_initSystemVariables(void);
CONTROLPILOT_STM32_EVSE_MODE HELPER_STM32_getCurrentStatus(void);
void HELPER_STM32_setCurrentStatus(CONTROLPILOT_STM32_EVSE_MODE newCurrentStatus);
uint8_t HELPER_STM32_getCurrentAmpere(void);
void HELPER_STM32_setCurrentAmpere(uint8_t newCurrentAmpere);
uint8_t HELPER_STM32_getMaximumAmpere(void);
void HELPER_STM32_setMaximumAmpere(uint8_t newMaximumAmpere);
void HELPER_STM32_updateLoop(void);
void delayMilliseconds (int milliseconds);