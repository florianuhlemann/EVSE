#include "stm32f0xx.h"
#include "usart_stm32_console.h"
#include "encoder_stm32.h"
#include "flash_stm32.h"


// Variable Declarations
volatile uint8_t ampSetting;
volatile uint8_t setupAmpSetting;
volatile uint8_t oldSetupAmpSetting;
volatile uint16_t encoderCounter;
volatile uint16_t encoderData = 0b00000000;
volatile Boolean setupMode = INACTIVE;
volatile Boolean firstTimeSetupMode = INACTIVE;


void ENCODER_STM32_setAmpere(uint8_t newAmpere) {
	USART_STM32_sendIntegerToUSART("A new ampere value has been set: ", newAmpere);
	ampSetting = newAmpere;
}


uint8_t ENCODER_STM32_getAmpere(void) {
	return ampSetting;
}


void ENCODER_STM32_configureInterface(void) {
	maximumAmpere = (uint8_t)(*MAXIMUM_AMPERE_ADDRPTR);
	ampSetting = maximumAmpere;
	setupAmpSetting = maximumAmpere;
	oldSetupAmpSetting = maximumAmpere;
	encoderCounter = maximumAmpere * ENCODER_STM32_STEP;
	ENCODER_STM32_initInterruptCLK();
	ENCODER_STM32_initInterruptDT();
	ENCODER_STM32_initInterruptSW();
	ENCODER_STM32_initTIM3();
}


void ENCODER_STM32_initInterruptCLK(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = ENCODER_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = ENCODER_EXTI_TRIGGER;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = ENCODER_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);

}


void ENCODER_STM32_initInterruptDT(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = ENCODER_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = ENCODER_EXTI_TRIGGER;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = ENCODER_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);
}


void ENCODER_STM32_initInterruptSW(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);

	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = ENCODER_EXTI_TRIGGER;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = ENCODER_NVIC_PRIORITY;
	NVIC_Init(&NVIC_InitStructure);
}


void ENCODER_STM32_initTIM3(void) {
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
	NVIC_InitStructure.NVIC_IRQChannelPriority = ENCODER_NVIC_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	TIM_SetCounter(TIM3, 0);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}


void ENCODER_STM32_startTIM3(void) {
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);
}


void ENCODER_STM32_stopTIM3(void) {
	TIM_Cmd(TIM3, DISABLE);
}


void ENCODER_STM32_updateAmpSetting(void) {

	if (setupMode != INACTIVE) {

		if (firstTimeSetupMode != INACTIVE) {
			// Setting current encoder position to current maximum ampere setting for user experience.
			encoderCounter = maximumAmpere * ENCODER_STM32_STEP;
			setupAmpSetting = maximumAmpere;
			firstTimeSetupMode = INACTIVE;
		} else {
			uint8_t newSetupAmpSetting = encoderCounter / ENCODER_STM32_STEP;
			if (newSetupAmpSetting != setupAmpSetting) {
				if (newSetupAmpSetting <= 1) {
					newSetupAmpSetting = 1;
					encoderCounter = newSetupAmpSetting * ENCODER_STM32_STEP;
				} else if (newSetupAmpSetting >= 32) {
					newSetupAmpSetting = 32;
					encoderCounter = 32 * ENCODER_STM32_STEP;
				} else {
					newSetupAmpSetting = encoderCounter / ENCODER_STM32_STEP;
				}
				if (newSetupAmpSetting != setupAmpSetting) {
					USART_STM32_sendIntegerToUSART("newSetupAmpSetting = ", newSetupAmpSetting);
					setupAmpSetting = newSetupAmpSetting;
				}
			}
		}


	} else {
		uint8_t oldAmpere = ENCODER_STM32_getAmpere();
		uint8_t newAmpere = encoderCounter / ENCODER_STM32_STEP;
		if (newAmpere != oldAmpere) {
			if (newAmpere <= 1) {
				newAmpere = 1;
				encoderCounter = newAmpere * ENCODER_STM32_STEP;
			} else if (newAmpere >= maximumAmpere) {
				newAmpere = maximumAmpere;
				encoderCounter = newAmpere * ENCODER_STM32_STEP;
			} else {
				newAmpere = encoderCounter / ENCODER_STM32_STEP;
			}
			if (newAmpere != oldAmpere) {
				ENCODER_STM32_setAmpere(newAmpere);
			}
		}
	}

}


void ENCODER_STM32_updateCounter(void) {

	encoderData = ((encoderData << 2) | (((ENCODER_GPIO_PORT->IDR & ENCODER_GPIO_DT_PIN) >> 1) | ((ENCODER_GPIO_PORT->IDR & ENCODER_GPIO_CLK_PIN) >> 1))) & 0b111111;
	if ((encoderData==30) | (encoderData==33) | (encoderData==40) | (encoderData==49) | (encoderData==56)) {
		encoderCounter = encoderCounter - 10;
		ENCODER_STM32_updateAmpSetting();
		// 1 rotation = 450
		//USART_STM32_sendIntegerToUSART("encoderCounter = ", encoderCounter);
	} else if ((encoderData==11) | (encoderData==16) | (encoderData==18) | (encoderData==45) | (encoderData==52)) {
		encoderCounter = encoderCounter + 10;
		ENCODER_STM32_updateAmpSetting();
		// 1 rotation = 615
		//USART_STM32_sendIntegerToUSART("encoderCounter = ", encoderCounter);
	}

}


void EXTI0_1_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line1) != RESET) {
		ENCODER_STM32_updateCounter();
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}


void EXTI2_3_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line2) != RESET) {
		ENCODER_STM32_updateCounter();
		EXTI_ClearITPendingBit(EXTI_Line2);
	}

}


void EXTI4_15_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line4) != RESET) {
		if ((ENCODER_GPIO_PORT->IDR & ENCODER_GPIO_SW_PIN) != RESET) {
			// SW has been released
			ENCODER_STM32_stopTIM3();
		} else {
			// SW has been pressed
			ENCODER_STM32_startTIM3();
		}
		//USART_STM32_sendStringToUSART("EXTI4_15_IRQHandler @ SW triggered");
		EXTI_ClearITPendingBit(EXTI_Line4);
	}

}


void TIM3_IRQHandler(void) {

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		ENCODER_STM32_stopTIM3();
		if (setupMode != INACTIVE) {
			setupMode = INACTIVE;
			USART_STM32_sendStringToUSART("setupMode INACTIVE");
			if (oldSetupAmpSetting != setupAmpSetting) {
				oldSetupAmpSetting = setupAmpSetting;
				FLASH_STM32_setNewMaximumAmpere(setupAmpSetting);
			}
		} else {
			setupMode = ACTIVE;
			firstTimeSetupMode = ACTIVE;
			USART_STM32_sendStringToUSART("setupMode ACTIVE");
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

