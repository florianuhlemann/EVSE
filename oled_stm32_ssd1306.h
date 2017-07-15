// OLED_STM32_OLED_STM32 library: This library shall enable interfacing an OLED_STM32 OLED based display on an STM32F0 chip.

// Pin Definitions
#define    OLED_GPIO_PORT1       GPIOA
#define    OLED_RCC_PERIPH1      RCC_AHBPeriph_GPIOA
#define    OLED_CS_PIN           GPIO_Pin_0
#define    OLED_RST_PIN          GPIO_Pin_3
#define    OLED_SCK_PIN          GPIO_Pin_5
#define    OLED_MOSI_PIN         GPIO_Pin_7

#define    OLED_GPIO_PORT2       GPIOB
#define    OLED_RCC_PERIPH2      RCC_AHBPeriph_GPIOB
#define    OLED_SS_PIN           GPIO_Pin_1


// SPI Definitions
#define    OLED_SPI_PORT         SPI1
#define    OLED_SPI_PERIPH       RCC_APB2Periph_SPI1
#define    OLED_SCK_PINSOURCE    GPIO_PinSource5
#define    OLED_MOSI_PINSOURCE   GPIO_PinSource7
#define    OLED_GPIO_AF          GPIO_AF_0
#define    OLED_SPI_COMMAND      0x00
#define    OLED_SPI_DATA         0x01

// Variable Definitions
#define    OLED_DISPLAY_WIDTH    128
#define    OLED_DISPLAY_HEIGHT   32
#define    HIGH                  Bit_SET
#define    LOW                   Bit_RESET
#define    COMMAND_BUFFER_LENGTH 21
#define    DISPLAY_BUFFER_LENGTH OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8


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
#define    OLED_CHGPUMPSETTING   0x8D
#define    OLED_SETCHGPUMP       0x10 // or 0x10=Disable 0x14=Enable
#define    OLED_DISPLAYON        0xAF
#define    OLED_FORCEDISPLAYON   0xA5

// Function Definitions

// Function Declarations
void OLED_STM32_configureInterface(void);
void OLED_STM32_initDisplay(void);
void OLED_STM32_sendDisplayBuffer(void);
void OLED_STM32_sendBuffer(uint8_t *buffer, uint8_t bufferType, uint16_t numberOfElements);
void OLED_STM32_digitalWrite(uint16_t GPIO_Pin, BitAction BitVal);
