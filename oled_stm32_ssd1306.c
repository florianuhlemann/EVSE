#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"
#include "helper_stm32.h"
#include "usart_stm32_console.h"


// Variable Declarations
uint8_t OLED_STM32_commandBuffer[COMMAND_BUFFER_LENGTH] = {0xAE,0xD5,0x80,0xA8,0x1F,0xD3,0x00,0x40,0x8D,0x14,0x20,0x00,0xA1,0xC8,0xDA,0x02,0x81,0x8F,0xD9,0xF1,0xDB,0x40,0x2E,0xA4,0xA6,0xAF};
uint8_t OLED_STM32_displayBuffer[DISPLAY_BUFFER_LENGTH] = {255,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,129,193,97,225,225,1,1,129,193,193,193,129,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,129,193,193,193,129,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,192,192,0,0,0,0,0,192,192,0,128,192,192,192,0,128,192,192,192,0,0,0,192,192,0,0,128,192,192,0,0,192,192,0,128,192,192,192,0,0,248,254,159,195,112,223,207,240,254,223,225,248,207,195,0,0,128,192,192,192,128,128,0,0,0,128,192,192,0,0,0,192,192,240,254,223,225,248,207,195,0,220,220,28,0,0,128,192,192,192,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,48,24,14,119,119,127,124,120,112,56,127,127,63,7,1,127,127,63,7,3,127,127,103,96,48,63,127,115,48,28,127,127,96,48,127,127,63,7,3,5,15,15,12,255,255,255,61,252,12,12,12,31,63,112,96,96,96,48,62,127,99,97,56,63,127,97,112,56,30,119,119,127,124,120,112,56,28,31,63,112,96,96,96,48,63,127,103,96,48,63,127,113,96,99,99,48,56,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,135,159,159,152,143,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,255};


// Command = D/C LOW
// Data = D/C HIGH
// delay before during and after reset 100ms

void OLED_STM32_configureInterface(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(OLED_RCC_PERIPH1, ENABLE);
	RCC_AHBPeriphClockCmd(OLED_RCC_PERIPH2, ENABLE);
	RCC_APB2PeriphClockCmd(OLED_SPI_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = OLED_GPIO_SPEED;
	GPIO_InitStructure.GPIO_Pin = OLED_SCK_PIN | OLED_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_PinAFConfig(OLED_GPIO_PORT1, OLED_SCK_PINSOURCE, OLED_GPIO_AF);
	GPIO_PinAFConfig(OLED_GPIO_PORT1, OLED_MOSI_PINSOURCE, OLED_GPIO_AF);
	GPIO_Init(OLED_GPIO_PORT1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN | OLED_DC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(OLED_GPIO_PORT1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = OLED_CS_PIN;
	GPIO_Init(OLED_GPIO_PORT2, &GPIO_InitStructure);

	// Initializing GPIO
	OLED_STM32_digitalWrite(OLED_RST_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_DC_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);

	// Configuring SPIx
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler	= OLED_SPI_PRESCALER; //4 or 8 works
	SPI_InitStructure.SPI_CPHA = OLED_SPI_CPHA;
	SPI_InitStructure.SPI_CPOL = OLED_SPI_CPOL;
	SPI_InitStructure.SPI_DataSize = OLED_SPI_DATASIZE;
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
	OLED_STM32_digitalWrite(OLED_RST_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	OLED_STM32_sendBuffer(OLED_STM32_commandBuffer, OLED_SPI_COMMAND, COMMAND_BUFFER_LENGTH);
	OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, DISPLAY_BUFFER_LENGTH);
	OLED_STM32_digitalWrite(OLED_DC_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);

}


// A function to send a uint8_t buffer array to the SSD1306 controller. Possible types are:
// OLED_SPI_COMMAND - This is used for all commands sent to the controller. D/C = LOW
// OLED_SPI_DATA - This is used for all display data transmission to the controller. D/C = HIGH
void OLED_STM32_sendBuffer(uint8_t *buffer, uint8_t bufferType, uint16_t numberOfElements) {

	if (bufferType == OLED_SPI_DATA) {
		OLED_STM32_digitalWrite(OLED_DC_PIN, HIGH);
	} else {
		OLED_STM32_digitalWrite(OLED_DC_PIN, LOW);
	}
	for (uint16_t i = 0; i < numberOfElements; i++) {
		SPI_SendData8(OLED_SPI_PORT, buffer[i]);
	}
    while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
    while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore

}


// Helper function for pulling OLED pins high or low.
// Example: OLED_STM32_digitalWrite(OLED_DC_PIN, HIGH);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal) {
	
	if (GPIO_Pin == OLED_CS_PIN) {
		GPIO_WriteBit(OLED_GPIO_PORT2, GPIO_Pin, BitVal);
	} else {
		GPIO_WriteBit(OLED_GPIO_PORT1, GPIO_Pin, BitVal);
	}

}
