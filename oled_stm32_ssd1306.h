// OLED_STM32_OLED_STM32 library: This library shall enable interfacing an OLED_STM32 OLED based display on an STM32F0 chip.

// Type Definitions
#ifndef EVSEMODE_H
#define EVSEMODE_H
typedef enum { DISCONNECTED = 0, CONNECTED_NO_PWM = 1, CONNECTED = 2, CHARGING = 3, CHARGING_COOLED = 4, FAULT = 5 } CONTROLPILOT_STM32_EVSE_MODE;
#endif /* EVSEMODE_H */

// Pin Definitions
#define    OLED_GPIO_PORT1       GPIOA
#define    OLED_RCC_PERIPH1      RCC_AHBPeriph_GPIOA
#define    OLED_GPIO_SPEED       GPIO_Speed_10MHz
#define    OLED_DC_PIN           GPIO_Pin_0
#define    OLED_RST_PIN          GPIO_Pin_3
#define    OLED_SCK_PIN          GPIO_Pin_5
#define    OLED_MOSI_PIN         GPIO_Pin_7

#define    OLED_GPIO_PORT2       GPIOB
#define    OLED_RCC_PERIPH2      RCC_AHBPeriph_GPIOB
#define    OLED_CS_PIN           GPIO_Pin_1


// SPI Definitions
#define    OLED_SPI_PORT         SPI1
#define    OLED_SPI_PERIPH       RCC_APB2Periph_SPI1
#define    OLED_SPI_PRESCALER    SPI_BaudRatePrescaler_4
#define    OLED_SPI_CPHA         SPI_CPHA_1Edge
#define    OLED_SPI_CPOL         SPI_CPOL_Low
#define    OLED_SPI_DATASIZE     SPI_DataSize_8b
#define    OLED_SCK_PINSOURCE    GPIO_PinSource5
#define    OLED_MOSI_PINSOURCE   GPIO_PinSource7
#define    OLED_GPIO_AF          GPIO_AF_0
#define    OLED_SPI_COMMAND      0x00
#define    OLED_SPI_DATA         0x01


// Variable Definitions
#define    OLED_DISPLAY_WIDTH    128
#define    OLED_DISPLAY_HEIGHT   64
#define    HIGH                  Bit_SET
#define    LOW                   Bit_RESET
#define    COMMAND_BUFFER_LENGTH 26
#define    DISPLAY_BUFFER_LENGTH OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8


// Parameter Definitions in correct order
#define    OLED_DISPLAYOFF       0xAE // turn display off
#define    OLED_SETCLOCKDIV      0xD5 // clock divide ratio
#define    OLED_CLOCKDIVSETTING  0x80 // oscillator frequency
#define    OLED_SETMULTIPLEX     0xA8 // set MUX ratio
#define    OLED_MULTIPLEXSETTING 0x3F // MUX ratio depends on height [0x1F = 32px] or [0x3F = 64px]
#define    OLED_SETDISPLAYOFFSET 0xD3 // Display Offset
#define    OLED_DISPLAYOFFSET    0x00 // Display Offset = 0
#define    OLED_SETSTARTLINE     0x40 // Set Start Line
#define    OLED_CHGPUMPSETTING   0x8D // Set Charge Pump Setting
#define    OLED_SETCHGPUMP       0x10 // Charge Pump Setting [0x10 = Disable] or [0x14 = Enable=32px]
#define    OLED_SETADDRESSMODE   0x20 // Page Addressing Mode
#define    OLED_HORZPAGEMODE     0x00 // Horizontal with auto new line
#define    OLED_SEGMENTREMAP     0xA1 // Segment Remap A0 / A1 (Mirroring Horizontally)
#define    OLED_SCANDIRECTION    0xC8 // Scan Direction C0 / C8 (Mirroring Vertically)
#define    OLED_SETCOMPINS       0xDA // Set COM pin HW config
#define    OLED_COMPINSSETTING   0x12 // sequential com pin config [0x02 = 32px] or [0x12 = 64px]
#define    OLED_SETCONTRAST      0x81 // Set Contrast
#define    OLED_CONTRASTSETTING  0x7F // Contrast Setting 8F / 7F
#define    OLED_SETPRECHGPERIOD  0xD9 // Set Precharge Period
#define    OLED_PRECHGPERIOD     0xF1 // precharge period = 22 / F1=64px+32px CONTRAST?
#define    OLED_SETVCOMHDESELECT 0xDB // set VCOMh deselect
#define    OLED_VCOMHDESELECTLVL 0x40 // VCOMh deselect level
#define    OLED_DISABLESCROLL    0x2E // Disable Scrolling
#define    OLED_FULLDISPLAYOFF   0xA4 // Set display to memory content
#define    OLED_SETNORMALDISPLAY 0xA6 // set non-inverted display
#define    OLED_DISPLAYON        0xAF // Turn display on


// Function Declarations
void OLED_STM32_configureInterface(void);
void OLED_STM32_initDisplay(void);
void OLED_STM32_sendBuffer(uint8_t *buffer, uint8_t bufferType, uint16_t numberOfElements);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal);
void OLED_STM32_generateBuffer(uint8_t xOffset, uint8_t yOffset, uint8_t pixelArray[], uint16_t arrayLength);
void OLED_STM32_updateDisplay(void);
void OLED_STM32_clearDisplay(void);
void OLED_STM32_drawPixel(uint8_t x, uint8_t y);
void OLED_STM32_updateMainView(void);
void OLED_STM32_updateSetupView(uint8_t currentAmpere);
void OLED_STM32_drawMonospaceCharacter(uint8_t xPosOffset, uint8_t yPosOffset, uint8_t myChar);
void OLED_STM32_drawMonospaceString(uint8_t xPos, uint8_t yPos, const char* myString);
uint8_t OLED_STM32_getMonospaceGlyphIndex(uint8_t charIndex);
void OLED_STM32_drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void OLED_STM32_drawLargeCharacter(uint8_t xPosOffset, uint8_t yPosOffset, uint8_t myChar);
void OLED_STM32_drawLargeString(uint8_t xPos, uint8_t yPos, const char* myString);
uint8_t OLED_STM32_getLargeGlyphIndex(uint8_t charIndex);
//void OLED_STM32_drawImage(uint8_t xPosOffset, uint8_t yPosOffset);

