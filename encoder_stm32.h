// ENCODER_STM32 library: This library shall enable interfacing an encoder on an STM32F0 chip.

// GPIO Definitions
#define    ENCODER_GPIO_PORT       GPIOA
#define    ENCODER_GPIO_CLK_PIN    GPIO_Pin_1
#define    ENCODER_GPIO_DT_PIN     GPIO_Pin_2
#define    ENCODER_GPIO_SW_PIN     GPIO_Pin_4
#define    ENCODER_GPIO_PERIPH     RCC_AHBPeriph_GPIOA

// EXTI Definitions
#define    ENCODER_EXTI_PORTSRC    EXTI_PortSourceGPIOA
#define    ENCODER_EXTI_CLK_PINSRC EXTI_PinSource1
#define    ENCODER_EXTI_CLK_LINE   EXTI_Line1
#define    ENCODER_EXTI_DT_PINSRC  EXTI_PinSource2
#define    ENCODER_EXTI_DT_LINE    EXTI_Line2
#define    ENCODER_EXTI_SW_PINSRC  EXTI_PinSource4
#define    ENCODER_EXTI_SW_LINE    EXTI_Line4
#define    ENCODER_EXTI_PERIPH     RCC_APB2Periph_SYSCFG
#define    ENCODER_EXTI_MODE       EXTI_Mode_Interrupt
#define    ENCODER_EXTI_TRIGGER    EXTI_Trigger_Falling

// NVIC Definitions
#define    ENCODER_NVIC_CLK_CHA    EXTI0_1_IRQn
#define    ENCODER_NVIC_DT_CHA     EXTI2_3_IRQn
#define    ENCODER_NVIC_SW_CHA     EXTI4_15_IRQn
#define    ENCODER_NVIC_PRIORITY   0x03

// Variable Definitions
typedef enum {ACTIVE = 0, INACTIVE = 1} Boolean;
typedef enum {FORWARD = 0, REVERSE = 1} Direction;

// Parameter Definitions

// Function Definitions

// Function Declarations
void ENCODER_STM32_initInterruptCLK(void);
void ENCODER_STM32_initInterruptDT(void);