#include "stm32f0xx.h"
#include "userbutton_stm32.h"
#include "helper_stm32.h"
//#include "usart_stm32_console.h"
#include "oled_stm32_ssd1306.h"


// Variable Declarations
volatile uint8_t setupAmpSetting;
volatile uint8_t oldSetupAmpSetting;
volatile Boolean setupMode = FALSE;


void USERBUTTON_STM32_configureInterface(void) {
	USERBUTTON_STM32_initInterruptUP();
	USERBUTTON_STM32_initInterruptENTER();
	USERBUTTON_STM32_initInterruptDOWN();
	USERBUTTON_STM32_initTIM3();
	setupAmpSetting = HELPER_STM32_getMaximumAmpere();
}


void USERBUTTON_STM32_initInterruptUP(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(USERBUTTON_GPIO_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = USERBUTTON_GPIO_UP_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(USERBUTTON_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(USERBUTTON_EXTI_PERIPH, ENABLE);
	SYSCFG_EXTILineConfig(USERBUTTON_EXTI_PORTSRC, USERBUTTON_EXTI_UP_PINSRC);

	EXTI_InitStructure.EXTI_Line = USERBUTTON_EXTI_UP_LINE;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = USERBUTTON_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = USERBUTTON_EXTI_TRIGGER;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = USERBUTTON_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);

}


void USERBUTTON_STM32_initInterruptENTER(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(USERBUTTON_GPIO_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = USERBUTTON_GPIO_ENTER_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(USERBUTTON_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(USERBUTTON_EXTI_PERIPH, ENABLE);
	SYSCFG_EXTILineConfig(USERBUTTON_EXTI_PORTSRC, USERBUTTON_EXTI_ENTER_PINSRC);

	EXTI_InitStructure.EXTI_Line = USERBUTTON_EXTI_ENTER_LINE;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = USERBUTTON_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = USERBUTTON_EXTI_TRIGGER_SETUP;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = USERBUTTON_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);
}


void USERBUTTON_STM32_initInterruptDOWN(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(USERBUTTON_GPIO_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = USERBUTTON_GPIO_DOWN_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(USERBUTTON_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(USERBUTTON_EXTI_PERIPH, ENABLE);
	SYSCFG_EXTILineConfig(USERBUTTON_EXTI_PORTSRC, USERBUTTON_EXTI_DOWN_PINSRC);

	EXTI_InitStructure.EXTI_Line = USERBUTTON_EXTI_DOWN_LINE;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = USERBUTTON_EXTI_TRIGGER;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = USERBUTTON_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);
}


void USERBUTTON_STM32_initTIM3(void) {
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	uint16_t myPrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000) - 1;
	uint16_t period = 1500;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = myPrescalerValue - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = USERBUTTON_NVIC_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	TIM_SetCounter(TIM3, 0);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}


void USERBUTTON_STM32_startTIM3(void) {
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);
}


void USERBUTTON_STM32_stopTIM3(void) {
	TIM_Cmd(TIM3, DISABLE);
}


void USERBUTTON_STM32_updateAmpSetting(int8_t ampChange) {

	if (setupMode == TRUE) {
		uint8_t newSetupAmpSetting = setupAmpSetting + ampChange;
		if (newSetupAmpSetting < 1) {
			newSetupAmpSetting = 1;
		} else if (newSetupAmpSetting > 32) {
			newSetupAmpSetting = 32;
		}
		if (newSetupAmpSetting != setupAmpSetting) {
			setupAmpSetting = newSetupAmpSetting;
			//USART_STM32_sendIntegerToUSART("newSetupAmpSetting = ", newSetupAmpSetting);
			OLED_STM32_updateSetupView(setupAmpSetting);
		}
	} else {
		uint8_t newAmpSetting = HELPER_STM32_getCurrentAmpere() + ampChange;
		if (newAmpSetting < 1) {
			newAmpSetting = 1;
		} else if (newAmpSetting > HELPER_STM32_getMaximumAmpere()) {
			newAmpSetting = HELPER_STM32_getMaximumAmpere();
		}
		if (newAmpSetting != HELPER_STM32_getCurrentAmpere()) {
			HELPER_STM32_setCurrentAmpere(newAmpSetting);
			OLED_STM32_updateMainView();
		}
	}

}


// UP User Button
void EXTI0_1_IRQHandler(void) {

	if(EXTI_GetITStatus(USERBUTTON_EXTI_UP_LINE) != RESET) {
		USERBUTTON_STM32_updateAmpSetting(1);
		EXTI_ClearITPendingBit(USERBUTTON_EXTI_UP_LINE);
	}

}


// ENTER User Button
void EXTI2_3_IRQHandler(void) {

	if(EXTI_GetITStatus(USERBUTTON_EXTI_ENTER_LINE) != RESET) {
		if ((USERBUTTON_GPIO_PORT->IDR & USERBUTTON_GPIO_ENTER_PIN) == RESET) {
			// ENTER has been released
			USERBUTTON_STM32_stopTIM3();
		} else {
			// ENTER has been pressed
			USERBUTTON_STM32_startTIM3();
		}
		EXTI_ClearITPendingBit(USERBUTTON_EXTI_ENTER_LINE);
	}

}


// DOWN User Button
void EXTI4_15_IRQHandler(void) {

	if(EXTI_GetITStatus(USERBUTTON_EXTI_DOWN_LINE) != RESET) {
		USERBUTTON_STM32_updateAmpSetting(-1);
		EXTI_ClearITPendingBit(USERBUTTON_EXTI_DOWN_LINE);
	}

}


void TIM3_IRQHandler(void) {

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		USERBUTTON_STM32_stopTIM3();
		if (setupMode == TRUE) {
			setupMode = FALSE;
			//USART_STM32_sendStringToUSART("setupMode FALSE");
			if (oldSetupAmpSetting != setupAmpSetting) {
				oldSetupAmpSetting = setupAmpSetting;
				HELPER_STM32_setMaximumAmpere(setupAmpSetting);
				if (HELPER_STM32_getCurrentAmpere() > setupAmpSetting) { HELPER_STM32_setCurrentAmpere(setupAmpSetting); }
				OLED_STM32_updateMainView();
				//OLED_STM32_updateMessageView("Please restart EVSE");
			}
		} else {
			setupMode = TRUE;
			oldSetupAmpSetting = setupAmpSetting;
			OLED_STM32_updateSetupView(setupAmpSetting);
			//USART_STM32_sendStringToUSART("setupMode TRUE");
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

