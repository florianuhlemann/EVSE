// OLED_STM32_OLED_STM32 library: This library shall enable interfacing an OLED_STM32 OLED based display on an STM32F0 chip.

// Pin Definitions
#define    OLED_GPIO_PORT        GPIOA
#define    OLED_RCC_PERIPH       RCC_AHBPeriph_GPIOA
#define    OLED_RST_PIN          GPIO_Pin_3
#define    OLED_SS_PIN           GPIO_Pin_4
#define    OLED_SCK_PIN          GPIO_Pin_5
#define    OLED_CS_PIN           GPIO_Pin_6
#define    OLED_MOSI_PIN         GPIO_Pin_7

// SPI Definitions
#define    OLED_SPI_PORT         SPI1
#define    OLED_SPI_PERIPH       RCC_APB2Periph_SPI1
#define    OLED_SCK_PINSOURCE    GPIO_PinSource5
#define    OLED_MOSI_PINSOURCE   GPIO_PinSource7
#define    OLED_GPIO_AF          GPIO_AF_0

// Variable Definitions
#define    OLED_DISPLAY_WIDTH    128
#define    OLED_DISPLAY_HEIGHT   32
#define    HIGH                  Bit_SET
#define    LOW                   Bit_RESET

// Parameter Definitions in correct order
#define    OLED_DISPLAYOFF       0xAE
#define    OLED_SETMULTIPLEX     0xA8
#define    OLED_MULTIPLEXSETTING 0x1F //32-1 = 31 = 0x1F -> height of display
#define    OLED_SETDISPLAYOFFSET 0xD3
#define    OLED_DISPLAYOFFSET    0x00
#define    OLED_SETSTARTLINE     0x40
#define    OLED_SEGMENTREMAP     0xA0
#define    OLED_SCANDIRECTION    0xC0
#define    OLED_SETCOMPINS       0xDA
#define    OLED_COMPINSSETTING   0x02
#define    OLED_SETCONTRAST      0x81
#define    OLED_CONTRASTSETTING  0x8F
#define    OLED_SETADDRESSMODE   0x20 //try without setting it
#define    OLED_HORZPAGEMODE     0x00 //try without setting it
#define    OLED_FULLDISPLAYOFF   0xA4
#define    OLED_SETNORMALDISPLAY 0xA6
#define    OLED_SETCLOCKDIV      0xD5
#define    OLED_CLOCKDIVSETTING  0x80
#define    OLED_SETCHGPUMP       0x8D
#define    OLED_CHGPUMPSETTING   0x14 // or 0x10
#define    OLED_DISPLAYON        0xAF

// Variable Declarations
uint8_t OLED_STM32_commandBuffer[] = {
	OLED_DISPLAYOFF, //maybe skip?
	OLED_SETMULTIPLEX,
	OLED_MULTIPLEXSETTING,
	OLED_SETDISPLAYOFFSET,
	OLED_DISPLAYOFFSET,
	OLED_SETSTARTLINE,
	OLED_SEGMENTREMAP,
	OLED_SCANDIRECTION,
	OLED_SETCOMPINS,
	OLED_COMPINSSETTING,
	OLED_SETCONTRAST,
	OLED_CONTRASTSETTING,
	OLED_FULLDISPLAYOFF,
	OLED_SETNORMALDISPLAY,
	OLED_SETCLOCKDIV,
	OLED_CLOCKDIVSETTING,
	OLED_SETCHGPUMP,
	OLED_CHGPUMPSETTING,
	OLED_DISPLAYON
};

uint8_t OLED_STM32_displayBuffer[] = {
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

// Function Definitions

// Function Declarations
void OLED_STM32_configureInterface(void);
void OLED_STM32_initDisplay(void);
void OLED_STM32_sendCommand(uint8_t myData);
void OLED_STM32_sendCommandBuffer(uint8_t *commandBuffer);
void OLED_STM32_sendDisplayBuffer(uint8_t *displayBuffer);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal);