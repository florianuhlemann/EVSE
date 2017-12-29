#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"
#include "helper_stm32.h"


// Variable Declarations
uint8_t OLED_STM32_commandBuffer[COMMAND_BUFFER_LENGTH] = {OLED_DISPLAYOFF, OLED_SETCLOCKDIV, OLED_CLOCKDIVSETTING, OLED_SETMULTIPLEX, OLED_MULTIPLEXSETTING, OLED_SETDISPLAYOFFSET, OLED_DISPLAYOFFSET, OLED_SETSTARTLINE, OLED_CHGPUMPSETTING, OLED_SETCHGPUMP, OLED_SETADDRESSMODE, OLED_HORZPAGEMODE, OLED_SEGMENTREMAP, OLED_SCANDIRECTION, OLED_SETCOMPINS, OLED_COMPINSSETTING, OLED_SETCONTRAST, OLED_CONTRASTSETTING, OLED_SETPRECHGPERIOD, OLED_PRECHGPERIOD, OLED_SETVCOMHDESELECT, OLED_VCOMHDESELECTLVL, OLED_DISABLESCROLL, OLED_FULLDISPLAYOFF, OLED_SETNORMALDISPLAY, OLED_DISPLAYON};
uint8_t OLED_STM32_displayBuffer[DISPLAY_BUFFER_LENGTH];

 // = {255, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 240, 248, 28, 28, 252, 248, 0, 0, 192, 224, 112, 56, 248, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 224, 112, 56, 248, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 224, 224, 32, 0, 0, 0, 0, 192, 224, 224, 0, 192, 192, 224, 224, 192, 0, 128, 192, 224, 224, 224, 0, 0, 0, 192, 224, 224, 0, 0, 128, 224, 224, 32, 0, 0, 192, 224, 224, 0, 128, 192, 224, 224, 224, 0, 0, 240, 255, 255, 207, 224, 56, 31, 111, 225, 224, 254, 255, 255, 248, 252, 111, 99, 96, 128, 192, 192, 224, 224, 224, 192, 192, 0, 0, 0, 0, 0, 192, 224, 224, 32, 0, 0, 96, 224, 224, 254, 255, 255, 248, 252, 111, 99, 96, 230, 239, 239, 15, 2, 0, 128, 192, 224, 224, 224, 224, 192, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 96, 112, 60, 223, 199, 207, 255, 252, 248, 192, 224, 126, 255, 255, 62, 7, 1, 125, 255, 255, 62, 7, 1, 121, 255, 255, 227, 224, 112, 62, 255, 255, 225, 112, 28, 255, 255, 231, 224, 96, 126, 255, 255, 60, 7, 3, 1, 15, 31, 31, 12, 254, 255, 255, 3, 253, 252, 12, 28, 12, 12, 31, 127, 127, 240, 224, 224, 224, 96, 126, 255, 255, 227, 224, 112, 127, 255, 255, 224, 96, 112, 60, 223, 199, 207, 255, 252, 248, 192, 224, 112, 63, 127, 127, 240, 224, 224, 224, 96, 126, 255, 255, 225, 224, 112, 63, 127, 255, 224, 224, 227, 227, 97, 112, 56, 24, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 127, 255, 240, 224, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 255};

// Command = D/C LOW
// Data = D/C HIGH
// delay before during and after reset 100ms
// displayBuffer has value 0-255 for 8 lines with bitshift

uint32_t CurrentX = 0;
uint32_t CurrentY = 0;


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
	SPI_InitStructure.SPI_BaudRatePrescaler	= OLED_SPI_PRESCALER;
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

	for (int i = 0; i < DISPLAY_BUFFER_LENGTH; i++) { OLED_STM32_displayBuffer[i] = 0; }
	OLED_STM32_digitalWrite(OLED_RST_PIN, LOW);
	OLED_STM32_digitalWrite(OLED_RST_PIN, HIGH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	OLED_STM32_sendBuffer(OLED_STM32_commandBuffer, OLED_SPI_COMMAND, COMMAND_BUFFER_LENGTH);
	OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, DISPLAY_BUFFER_LENGTH);
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
	if (bufferType == OLED_SPI_COMMAND) { OLED_STM32_digitalWrite(OLED_DC_PIN, HIGH); }

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


void OLED_STM32_updateDisplay(void) {

	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, DISPLAY_BUFFER_LENGTH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);

}


void OLED_STM32_drawPixel(uint8_t x, uint8_t y) {

	if ((x < OLED_DISPLAY_WIDTH) && (y < OLED_DISPLAY_HEIGHT)) {
		OLED_STM32_displayBuffer[x + (y / 8) * OLED_DISPLAY_WIDTH] |= 1 << (y % 8);
	}

}


void OLED_STM32_drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {
}


void OLED_STM32_generateBuffer(uint8_t xOffset, uint8_t yOffset, uint8_t pixelArray[], uint8_t arrayLength) {

	for (int x = 0; x < pixelArray[1]; x++) {
		for (int y = 0; y < pixelArray[0]; y++) {
			if (pixelArray[y * pixelArray[1] + x + 2]) {
				OLED_STM32_drawPixel(x + xOffset, y + yOffset);
			}
		}
	}

}

