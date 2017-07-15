// ENCODER_STM32 library: This library shall enable interfacing an encoder on an STM32F0 chip.

// GPIO Definitions
#define    ENCODER_GPIO_PORT      GPIOB
#define    ENCODER_GPIO_CLK_PIN   GPIO_Pin_3
#define    ENCODER_GPIO_DT_PIN    GPIO_Pin_4
#define    ENCODER_GPIO_SW_PIN    GPIO_Pin_5
#define    ENCODER_GPIO_PERIPH    RCC_AHBPeriph_GPIOB

// EXTI Definitions
#define    ENCODER_EXTI_PORTSRC   EXTI_PortSourceGPIOB
#define    ENCODER_EXTI_PINSRC    EXTI_PinSource5
#define    ENCODER_EXTI_PERIPH    RCC_APB2Periph_SYSCFG
#define    ENCODER_EXTI_LINE      EXTI_Line5
#define    ENCODER_EXTI_MODE      EXTI_Mode_Interrupt
#define    ENCODER_EXTI_TRIGGER   EXTI_Trigger_Falling

// NVIC Definitions
#define    ENCODER_NVIC_CHANNEL   EXTI4_15_IRQn
#define    ENCODER_NVIC_PRIORITY  0x03

// Variable Definitions

// Parameter Definitions

// Function Definitions

// Function Declarations
void ENCODER_STM32_configureInterface(void);