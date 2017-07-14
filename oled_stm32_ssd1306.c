#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"

void OLED_STM32_configureInterface(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(OLED_RCC_PERIPH, ENABLE);
	RCC_APB2PeriphClockCmd(OLED_SPI_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_PinAFConfig(OLED_GPIO_PORT, OLED_SCK_PINSOURCE, OLED_GPIO_AF);
	GPIO_PinAFConfig(OLED_GPIO_PORT, OLED_MOSI_PINSOURCE, OLED_GPIO_AF);
	GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN | OLED_SS_PIN | OLED_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure);

	// Configuring SPIx
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = SPI_CRCLength_8b;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(OLED_SPI_PORT, &SPI_InitStructure);
	SPI_Cmd(OLED_SPI_PORT, ENABLE);

}


// Execute initialization commands and configure display with initial command and display buffer.
void OLED_STM32_initDisplay(void) {

	OLED_STM32_digitalWrite(OLED_RST_PIN, LOW);
	// wait 100ms
	OLED_STM32_digitalWrite(OLED_RST_PIN, HIGH);
	// wait 100ms
	// init command Buffer?
	OLED_STM32_sendCommandBuffer(OLED_STM32_commandBuffer);
	OLED_STM32_sendDisplayBuffer(OLED_STM32_displayBuffer);
	// send initial image buffer

}


void OLED_STM32_sendCommand(uint8_t myData) {

	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_SS_PIN, LOW);
	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	SPI_SendData8(OLED_SPI_PORT, myData);
	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


void OLED_STM32_sendCommandBuffer(uint8_t *commandBuffer) {

	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_SS_PIN, LOW); // slave select
	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW); // command select LOW for commands
	// change to variable length of array
	for (int i = 0; i < 19; i++) {
		SPI_SendData8(OLED_SPI_PORT, commandBuffer[i]);
	}
	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


void OLED_STM32_sendDisplayBuffer(uint8_t *displayBuffer) {

	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_SS_PIN, LOW); // slave select
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH); // command select HIGH for data
	// change to variable length of array
	for (int i = 0; i < 512; i++) {
		SPI_SendData8(OLED_SPI_PORT, displayBuffer[i]);
	}
	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


// Helper function for pulling OLED pins high or low.
// Example: OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal) {

	GPIO_WriteBit(OLED_GPIO_PORT, GPIO_Pin, BitVal);

}
