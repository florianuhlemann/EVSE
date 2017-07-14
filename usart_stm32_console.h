// USART_STM32_CONSOLE library: This library shall enable interfacing an FTDI-based UART device to an STM32F0

// Pin Definitions
#define    USART_STM32_GPIO_PORT       GPIOA
#define    USART_STM32_GPIO_PERIPH     RCC_AHBPeriph_GPIOA
#define    USART_STM32_GPIO_TX_PIN     GPIO_Pin_9
#define    USART_STM32_GPIO_TX_PINSRC  GPIO_PinSource9
#define    USART_STM32_GPIO_RX_PIN     GPIO_Pin_10
#define    USART_STM32_GPIO_RX_PINSRC  GPIO_PinSource10

// USART Definitions
#define    USART_STM32_USART_PORT      USART1
#define    USART_STM32_USART_PERIPH    RCC_APB2Periph_USART1
#define    USART_STM32_USART_AF        GPIO_AF_1

// Variable Definitions

// Parameter Definitions
#define    USART_STM32_BAUDRATE        115200

// Variable Declarations

// Function Definitions

// Function Declarations
void USART_STM32_configureInterface(void);
void USART_STM32_sendToUSART(char const *givenString);
