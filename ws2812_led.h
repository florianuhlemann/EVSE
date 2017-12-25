// WS2812_STM32 library: This library shall enable interfacing with a WS2812-based LED array.

// Pin Definitions
#define    WS2812_GPIO_PORT      GPIOA
#define    WS2812_RCC_PERIPH     RCC_AHBPeriph_GPIOA
#define    WS2812_GPIO_SPEED     GPIO_Speed_10MHz
#define    WS2812_MOSI_PIN       GPIO_Pin_10

// Variable Definitions
#define    WS2812_NUM_LEDS       24

// Function Definitions

// Function Declarations
void WS2812_STM32_init(void);
void WS2812_STM32_setRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue);
void WS2812_STM32_sendToLED(void);
void WS2812_STM32_setNumberOfLED(uint8_t numberOfLED);