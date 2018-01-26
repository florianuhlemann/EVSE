// HELPER_STM32 library: This library provides helper functions and definitions for STM32F0 chip.


// Type Definitions
#ifndef EVSEMODE_H
#define EVSEMODE_H
typedef enum { DISCONNECTED = 0, CONNECTED_NO_PWM = 1, CONNECTED = 2, CHARGING = 3, CHARGING_COOLED = 4, FAULT = 5 } CONTROLPILOT_STM32_EVSE_MODE;
#endif /* EVSEMODE_H */


// Variable Definitions
#define		TS_CAL1_ADDRPTR						((uint16_t*) ((uint32_t) 0x1ffff7b8))
#define		HELPER_STM32_MOVINGAVERAGE			32


// Variable Declarations
volatile 	CONTROLPILOT_STM32_EVSE_MODE 		currentStatus;
volatile 	CONTROLPILOT_STM32_EVSE_MODE 		lastStatus;
volatile 	uint8_t 							currentAmpere;
volatile 	uint8_t 							maximumAmpere;
volatile 	uint16_t 							VsenseCurrent;
volatile	uint16_t							previousTempArray[HELPER_STM32_MOVINGAVERAGE];
volatile	uint8_t								needsUpdate;


// Function Declarations
void HELPER_STM32_initSystemClocks(void);
void HELPER_STM32_initSystemVariables(void);
CONTROLPILOT_STM32_EVSE_MODE HELPER_STM32_getCurrentStatus(void);
void HELPER_STM32_setCurrentStatus(CONTROLPILOT_STM32_EVSE_MODE newCurrentStatus);
uint8_t HELPER_STM32_getCurrentAmpere(void);
void HELPER_STM32_setCurrentAmpere(uint8_t newCurrentAmpere);
uint8_t HELPER_STM32_getMaximumAmpere(void);
void HELPER_STM32_setMaximumAmpere(uint8_t newMaximumAmpere);
void HELPER_STM32_setCurrentTemp(uint16_t VsenseCurrent);
int8_t HELPER_STM32_getCurrentTemp(void);
void HELPER_STM32_setNeedsUpdate(uint8_t newNeedsUpdate);
void HELPER_STM32_updateLoop(void);
void delayMilliseconds (int milliseconds);