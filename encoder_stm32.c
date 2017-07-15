#include "stm32f0xx.h"
#include "usart_stm32_console.h"
#include "encoder_stm32.h"
#include <stdio.h>


volatile Boolean CLK_Active = INACTIVE;
volatile Boolean DT_Active = INACTIVE;
volatile uint8_t previousState = 0x0;
volatile uint8_t prePreviousState = 0x0;
volatile uint8_t prePrePreviousState = 0x0;
volatile uint16_t counter = 24 * 3;
volatile uint8_t ampSetting = 24;
volatile uint8_t CLK_Previous_State = 0;
volatile uint8_t DT_Previous_State = 0;
volatile Direction direction = FORWARD;

void ENCODER_STM32_configureInterface(void) {
	ENCODER_STM32_initInterruptCLK();
	ENCODER_STM32_initInterruptDT();
	ENCODER_STM32_initInterruptSW();
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
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
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
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
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
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
	NVIC_Init(&NVIC_InitStructure);
}


void ENCODER_STM32_updateAmpSetting(void) {

	if (counter / 3 != ampSetting) {
		ampSetting = counter / 3;
		char str[20];
		sprintf(str, "Ampere = %d", counter / 3);
		USART_STM32_sendToUSART(str);
	}

}


uint16_t ENCODER_STM32_stateConfig(void) {

	uint8_t currentState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) | GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) << 1;
	prePrePreviousState = prePreviousState;
	prePreviousState = previousState;
	previousState = currentState;
	return currentState | previousState << 1 | prePreviousState << 2 | prePrePreviousState << 4;

}


void ENCODER_STM32_updateCounter(uint16_t stateConfig) {

	// left turns
	if ( stateConfig == 24 || stateConfig == 35 || stateConfig == 40 || stateConfig == 51 || stateConfig == 56 ) {
		if (counter > 1) {
			counter = counter - 1;
		} else {
			counter = 0;
		}
	}
	// right turns
	if ( stateConfig == 20 || stateConfig == 36 || stateConfig == 52 || stateConfig == 55 || stateConfig == 57 ) {
		if (counter < 95) {
			counter = counter + 2;
		} else if (counter < 96) {
			counter = counter + 1;
		} else {
			counter = 96;
		}
	}
	ENCODER_STM32_updateAmpSetting();

}


void EXTI0_1_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line1) != RESET) {
		ENCODER_STM32_updateCounter(ENCODER_STM32_stateConfig());
		//USART_STM32_sendToUSART("EXTI0_1_IRQHandler @ CLK triggered");
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}


void EXTI2_3_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line2) != RESET) {
		ENCODER_STM32_updateCounter(ENCODER_STM32_stateConfig());
		//USART_STM32_sendToUSART("EXTI2_3_IRQHandler @ DT triggered");
		EXTI_ClearITPendingBit(EXTI_Line2);
	}

}


void EXTI4_15_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line4) != RESET) {
		USART_STM32_sendToUSART("SW pushed.");
		EXTI_ClearITPendingBit(EXTI_Line4);
	}

}