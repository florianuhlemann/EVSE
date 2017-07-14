#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"

void SSD1306_configureSpiInterface(void) {

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
void SSD1306_initDisplay(void) {

	SSD1306_digitalWrite(OLED_RST_PIN, LOW);
	// wait 100ms
	SSD1306_digitalWrite(OLED_RST_PIN, HIGH);
	// wait 100ms
	// init command Buffer?
	SSD1306_sendCommandBuffer(SSD1306_commandBuffer);
	SSD1306_sendDisplayBuffer(SSD1306_displayBuffer);
	// send initial image buffer

}


void SSD1306_sendCommand(uint8_t myData) {

	SSD1306_digitalWrite(OLED_SS_PIN, HIGH);
	SSD1306_digitalWrite(OLED_SS_PIN, LOW);
	SSD1306_digitalWrite(OLED_CS_PIN, LOW);
	SPI_SendData8(OLED_SPI_PORT, myData);
	SSD1306_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


void SSD1306_sendCommandBuffer(uint8_t *commandBuffer) {

	SSD1306_digitalWrite(OLED_SS_PIN, HIGH);
	SSD1306_digitalWrite(OLED_SS_PIN, LOW); // slave select
	SSD1306_digitalWrite(OLED_CS_PIN, LOW); // command select LOW for commands
	// change to variable length of array
	for (int i = 0; i < 19; i++) {
		SPI_SendData8(OLED_SPI_PORT, commandBuffer[i]);
	}
	SSD1306_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


void SSD1306_sendDisplayBuffer(uint8_t *displayBuffer) {

	SSD1306_digitalWrite(OLED_SS_PIN, HIGH);
	SSD1306_digitalWrite(OLED_SS_PIN, LOW); // slave select
	SSD1306_digitalWrite(OLED_CS_PIN, HIGH); // command select HIGH for data
	// change to variable length of array
	for (int i = 0; i < 512; i++) {
		SPI_SendData8(OLED_SPI_PORT, displayBuffer[i]);
	}
	SSD1306_digitalWrite(OLED_SS_PIN, HIGH); // We are done with this SPI device

}


// Helper function for pulling OLED pins high or low.
// Example: SSD1306_digitalWrite(OLED_CS_PIN, HIGH);
void SSD1306_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal) {

	GPIO_WriteBit(OLED_GPIO_PORT, GPIO_Pin, BitVal);

}
