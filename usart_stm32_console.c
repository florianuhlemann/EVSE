#include "stm32f0xx.h"
#include "usart_stm32_console.h"
#include "string.h"

void USART_STM32_configureInterface(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(USART_STM32_GPIO_PERIPH, ENABLE);
	RCC_APB2PeriphClockCmd(USART_STM32_USART_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = USART_STM32_GPIO_TX_PIN | USART_STM32_GPIO_RX_PIN;
	GPIO_PinAFConfig(USART_STM32_GPIO_PORT, USART_STM32_GPIO_TX_PINSRC, USART_STM32_USART_AF);
	GPIO_PinAFConfig(USART_STM32_GPIO_PORT, USART_STM32_GPIO_RX_PINSRC, USART_STM32_USART_AF);
	GPIO_Init(USART_STM32_GPIO_PORT, &GPIO_InitStructure);

	// Configuring USARTx
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = USART_STM32_BAUDRATE;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART_STM32_USART_PORT, &USART_InitStructure);
	USART_Cmd(USART_STM32_USART_PORT, ENABLE);

}

void USART_STM32_sendToUSART(char const *givenString) {
	
	for (int i = 0; i < strlen(givenString); i++) {
		USART_SendData(USART_STM32_USART_PORT, givenString[i]);
		while(USART_GetFlagStatus(USART_STM32_USART_PORT, USART_FLAG_TC) == RESET) {
			// wait for buffer to clear
		}
	}
	USART_SendData(USART_STM32_USART_PORT, 0x0A);
	USART_SendData(USART_STM32_USART_PORT, 0x0D);
	while(USART_GetFlagStatus(USART_STM32_USART_PORT, USART_FLAG_TC) == RESET) {
			// wait for buffer to clear
	}
}
