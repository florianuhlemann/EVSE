#include "stm32f0xx.h"
#include "helper_stm32.h"
#include "flash_stm32.h"
#include "oled_stm32_ssd1306.h"


volatile CONTROLPILOT_STM32_EVSE_MODE currentStatus;
volatile CONTROLPILOT_STM32_EVSE_MODE lastStatus;
volatile uint8_t currentAmpere;
volatile uint8_t maximumAmpere;
uint8_t loopCounter;


void HELPER_STM32_initSystemClocks(void) {

	// Reset config and disable external clock sources
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_OFF);
	RCC_LSEConfig(RCC_LSE_OFF);

	// Enable internal clock sources and wait until ready
	RCC_HSICmd(ENABLE);
	RCC_LSICmd(ENABLE);
	RCC_HSI14Cmd(ENABLE);
	while (!RCC_GetFlagStatus(RCC_FLAG_HSIRDY)) { /* wait until ready */ }
	while (!RCC_GetFlagStatus(RCC_FLAG_LSIRDY)) { /* wait until ready */ }
	while (!RCC_GetFlagStatus(RCC_FLAG_HSI14RDY)) { /* wait until ready */ }

	// Configure PLL to use HSI and wait until ready
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	while (!RCC_GetFlagStatus(RCC_FLAG_PLLRDY)) { /* wait until ready */ }

	// Configure system clocks to use PLL clock source and configure HSI14 for ADC
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
	RCC_ADCCLKConfig(RCC_ADCCLK_HSI14);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //useful?
	
}


// This function sets the main EVSE related variables and checks if the maximum current
// value has ever been stored in the FLASH ROM before. If not, it is set to 32A.
void HELPER_STM32_initSystemVariables(void) {

	maximumAmpere = FLASH_STM32_getMaximumAmpere();
	if ((maximumAmpere == 0) | (maximumAmpere > 32)) {
		FLASH_STM32_setNewMaximumAmpere(32);
		maximumAmpere = 32;
	}
	currentAmpere = maximumAmpere;
	currentStatus = DISCONNECTED;
	lastStatus = DISCONNECTED;
	loopCounter = 0;

}


CONTROLPILOT_STM32_EVSE_MODE HELPER_STM32_getCurrentStatus(void) {

	return currentStatus;

}


void HELPER_STM32_setCurrentStatus(CONTROLPILOT_STM32_EVSE_MODE newCurrentStatus) {

	currentStatus = newCurrentStatus;

}


uint8_t HELPER_STM32_getCurrentAmpere(void) {

	return currentAmpere;

}


void HELPER_STM32_setCurrentAmpere(uint8_t newCurrentAmpere) {

	currentAmpere = newCurrentAmpere;

}


uint8_t HELPER_STM32_getMaximumAmpere(void) {

	return maximumAmpere;

}


void HELPER_STM32_setMaximumAmpere(uint8_t newMaximumAmpere) {

	maximumAmpere = newMaximumAmpere;
	FLASH_STM32_setNewMaximumAmpere(maximumAmpere);

}


void HELPER_STM32_updateLoop(void) {

	while (1) {
		CONTROLPILOT_STM32_EVSE_MODE myStatus = currentStatus;
		if (lastStatus != myStatus) {
			OLED_STM32_updateMainView();
			lastStatus = myStatus;
		}
	}

}


// A delay function based purely on the performance of the microprocessor.
void delayMilliseconds (int milliseconds) {

	uint64_t counter = 2175 * milliseconds; //for 48MHz setting
	while (counter > 0) {
		counter--;
	}

}


/*
void delayMicroseconds (int microseconds) {
	uint64_t counter = microseconds; //for 48MHz setting
	while (counter > 0) {
		counter--;
	}
}
*/