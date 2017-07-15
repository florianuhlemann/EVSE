#include "stm32f0xx.h"
#include "usart_stm32_console.h"
#include "encoder_stm32.h"

void ENCODER_STM32_configureInterface(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(ENCODER_GPIO_PERIPH, ENABLE);
	RCC_APB2PeriphClockCmd(ENCODER_EXTI_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = ENCODER_GPIO_CLK_PIN | ENCODER_GPIO_DT_PIN | ENCODER_GPIO_SW_PIN;
	GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStructure);

	// Configuring EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = ENCODER_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = ENCODER_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = ENCODER_EXTI_TRIGGER;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	SYSCFG_EXTILineConfig(ENCODER_EXTI_PORTSRC, EXTI_PinSource5);
	EXTI_Init(&EXTI_InitStructure);

	// Configuring NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_NVIC_CHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPriority = ENCODER_NVIC_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}


void EXTI4_15_IRQHandler(void) {

	if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		USART_STM32_sendToUSART("ENCODER pressed.");
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	
}