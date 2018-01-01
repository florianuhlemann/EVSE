#include "stm32f0xx.h"
#include "oled_stm32_ssd1306.h"
#include "helper_stm32.h"
#include "font8x8_basic.h"
#include <math.h>


// Variable Declarations
uint8_t OLED_STM32_commandBuffer[COMMAND_BUFFER_LENGTH] = {OLED_DISPLAYOFF, OLED_SETCLOCKDIV, OLED_CLOCKDIVSETTING, OLED_SETMULTIPLEX, OLED_MULTIPLEXSETTING, OLED_SETDISPLAYOFFSET, OLED_DISPLAYOFFSET, OLED_SETSTARTLINE, OLED_CHGPUMPSETTING, OLED_SETCHGPUMP, OLED_SETADDRESSMODE, OLED_HORZPAGEMODE, OLED_SEGMENTREMAP, OLED_SCANDIRECTION, OLED_SETCOMPINS, OLED_COMPINSSETTING, OLED_SETCONTRAST, OLED_CONTRASTSETTING, OLED_SETPRECHGPERIOD, OLED_PRECHGPERIOD, OLED_SETVCOMHDESELECT, OLED_VCOMHDESELECTLVL, OLED_DISABLESCROLL, OLED_FULLDISPLAYOFF, OLED_SETNORMALDISPLAY, OLED_DISPLAYON};
uint8_t OLED_STM32_displayBuffer[DISPLAY_BUFFER_LENGTH];


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


// This function send the current array of the OLED buffer to the device over SPI.
void OLED_STM32_updateDisplay(void) {

	OLED_STM32_digitalWrite(OLED_CS_PIN, LOW);
	OLED_STM32_sendBuffer(OLED_STM32_displayBuffer, OLED_SPI_DATA, DISPLAY_BUFFER_LENGTH);
	OLED_STM32_digitalWrite(OLED_CS_PIN, HIGH);

}


// This function clears the array of the OLED buffer.
// The OLED buffer needs to be sent when drawing is completed by another call.
void OLED_STM32_clearDisplay(void) {

	for (int i = 0; i < DISPLAY_BUFFER_LENGTH; i++) { OLED_STM32_displayBuffer[i] = 0; }
	//OLED_STM32_updateDisplay();

}


// This function can place an individual pixel as active into the array of the OLED buffer.
// The OLED buffer needs to be sent when drawing is completed by another call.
void OLED_STM32_drawPixel(uint8_t x, uint8_t y) {

	if ((x < OLED_DISPLAY_WIDTH) && (y < OLED_DISPLAY_HEIGHT)) {
		OLED_STM32_displayBuffer[x + (y / 8) * OLED_DISPLAY_WIDTH] |= 1 << (y % 8);
	}

}


// This function is drawing each 8px tall character glyph into the array of the OLED buffer.
// The OLED buffer needs to be sent when drawing is completed by another call.
void OLED_STM32_drawMonospaceCharacter(uint8_t xPosOffset, uint8_t yPosOffset, uint8_t myChar) {
	
	for (int yPos = 0; yPos < 8; yPos++) {
		for (int xPos = 0; xPos < 8; xPos++) {
			uint8_t myValue = (monospaceFont[OLED_STM32_getMonospaceGlyphIndex(myChar)][yPos] & (1<<xPos)) / (pow(2, xPos));
			if (myValue == 1) { OLED_STM32_drawPixel(xPos + xPosOffset, yPos + yPosOffset); }
		}
	}

}


// This function takes the given string, checks for non-'\n' characters and advances the x-Position by the width of the glyph.
// When the full string is drawn, the updated OLED buffer is sent to the device.
void OLED_STM32_drawMonospaceString(uint8_t xPos, uint8_t yPos, const char* myString) {

	int counter = 0;
	uint8_t currentPosX = xPos;
	while (myString[counter] != 0) {
		OLED_STM32_drawMonospaceCharacter(currentPosX, yPos, myString[counter]);
		currentPosX += monospaceFontWidth[OLED_STM32_getMonospaceGlyphIndex(myString[counter])];
		counter++;
	}
	OLED_STM32_updateDisplay();
	
}


// This is a helper function to calcualte the correct font glyph index for any given character
uint8_t OLED_STM32_getMonospaceGlyphIndex(uint8_t charIndex) {

	switch (charIndex) {
		case 0xC4: return 95;
		case 0xE4: return 96;
		case 0xD6: return 97;
		case 0xF6: return 98;
		case 0xDC: return 99;
		case 0xFC: return 100;
		case 0xDF: return 101;
		default: return charIndex - 32;
	}

}


void OLED_STM32_drawImage(uint8_t xPosOffset, uint8_t yPosOffset) {

	uint8_t correctionFactor = 0;
	if (imageWidth % 8 > 0) { correctionFactor = 1; }
	for (int yPos = 0; yPos < imageHeight; yPos++) {
		for (int xPos = 0; xPos < imageWidth; xPos++) {
			uint16_t currentBit = xPos / 8 + (yPos * (imageWidth / 8 + correctionFactor));
			uint8_t currentBitMask = 1 << xPos % 8;
			uint8_t myValue = (imageBits[currentBit] & currentBitMask) / currentBitMask;
			if (myValue) { OLED_STM32_drawPixel(xPos + xPosOffset, yPos + yPosOffset); }
		}
	}
	OLED_STM32_updateDisplay();

}


void OLED_STM32_drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	// Do something to create a line. Diagonal is tricky.
	for (int x = 0; x <= (xEnd - xStart); x++) {
		for (int y = 0; y <= (yEnd - yStart); y++) {
			OLED_STM32_drawPixel(xStart + x, yStart + y);
		}
	}

}



// This function is drawing a larger font glyph into the array of the OLED buffer.
// This can only be used for characters 0-9, ' ' and 'A'.
// The OLED buffer needs to be sent when drawing is completed by another call.
void OLED_STM32_drawLargeCharacter(uint8_t xPosOffset, uint8_t yPosOffset, uint8_t myChar) {

	uint8_t glyphWidth = latoGlyphWidth[OLED_STM32_getLargeGlyphIndex(myChar)];
    const uint8_t *imageBits = latoFontBits[OLED_STM32_getLargeGlyphIndex(myChar)];
	uint8_t correctionFactor = 0;
	if (latoFontWidth % 8 > 0) { correctionFactor = 1; }
	for (int yPos = 0; yPos < latoFontHeight; yPos++) {
		for (int xPos = 0; xPos < glyphWidth; xPos++) {
			uint16_t currentBit = xPos / 8 + (yPos * (latoFontWidth / 8 + correctionFactor));
			uint8_t currentBitMask = 1 << xPos % 8;
			uint8_t myValue = (imageBits[currentBit] & currentBitMask) / currentBitMask;
			if (myValue) { OLED_STM32_drawPixel(xPos + xPosOffset + latoGlyphOffset[OLED_STM32_getLargeGlyphIndex(myChar)], yPos + yPosOffset); }
		}
	}

}


// This function takes the given string, checks for non-'\n' characters and advances the x-Position by the width of the glyph.
// When the full string is drawn, the updated OLED buffer is sent to the device.
void OLED_STM32_drawLargeString(uint8_t xPos, uint8_t yPos, const char* myString) {

	int counter = 0;
	uint8_t currentPosX = xPos;
	while (myString[counter] != 0) {
		OLED_STM32_drawLargeCharacter(currentPosX, yPos, myString[counter]);
		currentPosX += latoGlyphWidth[OLED_STM32_getLargeGlyphIndex(myString[counter])] + latoGlyphOffset[OLED_STM32_getLargeGlyphIndex(myString[counter])];
		counter++;
	}
	OLED_STM32_updateDisplay();
	
}


// This is a helper function to calculate the correct font glyph index for 0-9, ' ' and 'A'
uint8_t OLED_STM32_getLargeGlyphIndex(uint8_t charIndex) {

	switch (charIndex) {
        case 32: return 0;
		case 65: return 11;
		default: return charIndex - 47;
	}

}

