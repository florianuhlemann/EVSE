#include "stm32f0xx.h"
#include "helper_stm32.h"


void HELPER_STM32_initSystemClocks(void) {

	// Reset config and disable external clock sources
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_OFF);
	RCC_LSEConfig(RCC_LSE_OFF);

	// Enable internal clock sources and wait until ready
	RCC_HSICmd(ENABLE);
	RCC_LSICmd(ENABLE);
	while (!RCC_GetFlagStatus(RCC_FLAG_HSIRDY)) { /* wait until ready */ }
	while (!RCC_GetFlagStatus(RCC_FLAG_LSIRDY)) { /* wait until ready */ }

	// Configure PLL to use HSI and wait until ready
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
	RCC_PLLCmd(ENABLE);
	while (!RCC_GetFlagStatus(RCC_FLAG_PLLRDY)) { /* wait until ready */ }

	// Configure system clocks to use PLL clock source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); //useful?

	// Configure ADC clocks
	RCC_HSI14Cmd(ENABLE);
	RCC_ADCCLKConfig(RCC_ADCCLK_HSI14);
	
}


void delayMilliseconds (int milliseconds) {
	uint64_t counter = 2175 * milliseconds; //for 8MHz setting
	//uint64_t counter = 379 * milliseconds; //for 8MHz setting
	//uint64_t counter = 187 * milliseconds;
	while (counter > 0) {
		counter--;
	}
}

/*
void createDisplayBuffer(void) {
	for (int i=0; i<512;i++) {
		OLED_STM32_displayBuffer[i] = 0xAD;
	}
}
*/