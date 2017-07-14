#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"
#include "helper_stm32.h"

// Variable Declarations
uint8_t OLED_STM32_commandBuffer[] = {
	0xAE,
	0x20,
	0x10,
	0xB0,
	0xC8,
	0x00,
	0x10,
	0x40,
	0x81,
	0xFF,
	0xA1,
	0xA6,
	0xA8,
	0x3F,
	0xA4,
	0xD3,
	0x00,
	0xD5,
	0xF0,
	0xD9,
	0x22,
	0xDA,
	0x12,
	0xDB,
	0x20,
	0x8D,
	0x14,
	0xAF
};

uint8_t OLED_STM32_displayBuffer[512] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,128,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,227,0,0,128,3,0,
	0,0,0,0,0,0,0,0,0,96,243,1,0,192,7,0,0,0,0,0,0,0,0,0,0,96,179,1,0,192,6,0,0,
	0,0,0,0,0,0,0,0,112,155,1,0,96,6,0,0,0,0,0,0,0,0,0,0,48,155,0,0,96,114,0,0,
	0,0,0,0,0,0,0,0,56,219,0,0,96,115,0,0,0,0,0,0,0,0,0,0,184,93,0,0,112,113,0,
	0,0,0,0,0,0,0,0,0,152,108,0,0,176,1,0,0,0,0,0,24,204,57,198,204,217,255,113,
	96,252,55,60,0,0,0,0,28,236,61,230,236,121,255,249,113,252,55,62,0,0,0,0,28,
	254,63,103,254,61,12,220,113,48,56,55,0,0,0,0,30,222,63,103,190,29,12,206,
	120,48,56,51,0,0,0,0,62,222,59,115,222,255,15,198,248,56,56,3,0,0,0,0,115,
	207,25,115,142,255,15,230,204,61,24,131,1,0,0,128,253,207,153,127,15,124,28,
	231,254,127,156,199,1,0,0,128,252,207,249,239,15,124,248,255,247,231,255,
	255,0,0,0,0,252,198,120,230,6,92,240,156,243,195,115,62,0,0,0,0,0,0,0,0,0,
	92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,92,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,120,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

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

	// Initializing GPIO
	GPIO_SetBits(OLED_GPIO_PORT, OLED_RST_PIN);
	GPIO_SetBits(OLED_GPIO_PORT, OLED_SS_PIN);
	GPIO_SetBits(OLED_GPIO_PORT, OLED_CS_PIN);


	// Configuring SPIx
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 8;
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
	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	delayMilliseconds(25);
	OLED_STM32_sendBuffer(OLED_STM32_commandBuffer, OLED_SPI_COMMAND);
	delayMilliseconds(25);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
	delayMilliseconds(25);
	OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA);
	delayMilliseconds(25);
	OLED_STM32_digitalWrite(OLED_SS_PIN, HIGH);

}


// A function to send a uint8_t buffer array to the SSD1306 controller. Possible types are:
// OLED_SPI_COMMAND - This is used for all commands sent to the controller.
// OLED_SPI_DATA - This is used for all display data transmission to the controller.
void OLED_STM32_sendBuffer(uint8_t *buffer, uint8_t bufferType) {

	if (bufferType == OLED_SPI_DATA) {
		OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
		delayMilliseconds(50);
	} else {
		OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
		delayMilliseconds(50);
	}
	int length = sizeof(buffer) / sizeof(uint8_t);
	for (int i = 0; i < length; i++) {
		SPI_SendData8(OLED_SPI_PORT, buffer[i]);
	}

}


// Helper function for pulling OLED pins high or low.
// Example: OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal) {

	GPIO_WriteBit(OLED_GPIO_PORT, GPIO_Pin, BitVal);

}
