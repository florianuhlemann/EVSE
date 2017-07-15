#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"
#include "helper_stm32.h"
#include "usart_stm32_console.h"


// Variable Declarations
uint8_t OLED_STM32_commandBuffer[COMMAND_BUFFER_LENGTH] = {
	0xAE,
	0xA8,
	0x1F,
	0xD3,
	0x00,
	0x40,
	0xA0,
	0xC0,
	0xDA,
	0x02,
	0x81,
	0x8F,
	0x20,
	0x00,
	0xA4,
	0xA6,
	0xD5,
	0x80,
	0x8D,
	0x10,
	0xAF
};


void OLED_STM32_configureInterface(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(OLED_RCC_PERIPH, ENABLE);
	RCC_APB2PeriphClockCmd(OLED_SPI_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_PinAFConfig(OLED_GPIO_PORT, OLED_SCK_PINSOURCE, OLED_GPIO_AF);
	GPIO_PinAFConfig(OLED_GPIO_PORT, OLED_MOSI_PINSOURCE, OLED_GPIO_AF);
	GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN | OLED_SS_PIN | OLED_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStructure);

	// Initializing GPIO
	GPIO_SetBits(OLED_GPIO_PORT, OLED_RST_PIN);
	GPIO_SetBits(OLED_GPIO_PORT, OLED_SS_PIN);
	GPIO_SetBits(OLED_GPIO_PORT, OLED_CS_PIN);


	// Configuring SPIx
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 10;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(OLED_SPI_PORT, &SPI_InitStructure);
	SPI_Cmd(OLED_SPI_PORT, ENABLE);

}


// Execute initialization commands and configure display with initial command and display buffer.
void OLED_STM32_initDisplay(void) {

	OLED_STM32_digitalWrite(OLED_RST_PIN, LOW);
	delayMilliseconds(100);
	OLED_STM32_digitalWrite(OLED_RST_PIN, HIGH);
	delayMilliseconds(25);
	OLED_STM32_digitalWrite(OLED_SS_PIN, LOW);
	delayMilliseconds(25);
	OLED_STM32_sendBuffer(OLED_STM32_commandBuffer, OLED_SPI_COMMAND, COMMAND_BUFFER_LENGTH);
	delayMilliseconds(25);
	//OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, DISPLAY_BUFFER_LENGTH);
	delayMilliseconds(25);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
	delayMilliseconds(25);
	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH);

}


void OLED_STM32_sendDisplayBuffer(void) {

	//OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, 512);

}


// A function to send a uint8_t buffer array to the SSD1306 controller. Possible types are:
// OLED_SPI_COMMAND - This is used for all commands sent to the controller.
// OLED_SPI_DATA - This is used for all display data transmission to the controller.
void OLED_STM32_sendBuffer(uint8_t *buffer, uint8_t bufferType, uint16_t numberOfElements) {

	if (bufferType == OLED_SPI_DATA) {
		OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
		delayMilliseconds(25);
	} else {
		OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
		delayMilliseconds(25);
	}
	for (uint16_t i = 0; i < numberOfElements; i++) {
		SPI_SendData8(OLED_SPI_PORT, buffer[i]);
	}

    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore

}


// Helper function for pulling OLED pins high or low.
// Example: OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal) {

	GPIO_WriteBit(OLED_GPIO_PORT, GPIO_Pin, BitVal);

}
