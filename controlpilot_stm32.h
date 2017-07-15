// CONTROLPILOT_STM32 library: This library shall enable the J1772 Control Pilot Signal on an STM32F0 chip.

// GPIO Definitions
#define    CONTROLPILOT_STM32_GPIO_PERIPH        RCC_AHBPeriph_GPIOB
#define    CONTROLPILOT_STM32_GPIO_PORT          GPIOB
#define    CONTROLPILOT_STM32_GPIO_PIN           GPIO_Pin_2

// TIM Definitions
#define    CONTROLPILOT_STM32_TIMER_HIGH         TIM2
#define    CONTROLPILOT_STM32_TIMER_LOW          TIM3
#define    CONTROLPILOT_STM32_TIMER_HIGH_PRIO    0x02
#define    CONTROLPILOT_STM32_TIMER_LOW_PRIO     0x02
#define    CONTROLPILOT_STM32_TIMER_HIGH_IRQ     TIM2_IRQn
#define    CONTROLPILOT_STM32_TIMER_LOW_IRQ      TIM3_IRQn
#define    CONTROLPILOT_STM32_TIMER_HIGH_PERIPH  RCC_APB1Periph_TIM2
#define    CONTROLPILOT_STM32_TIMER_LOW_PERIPH   RCC_APB1Periph_TIM3

// Variable Definitions
#define CONTROLPILOT_STM32_TIMER_HIGH_PERIOD     1001
#define CONTROLPILOT_STM32_TIMER_LOW_PERIOD      320

// Parameter Definitions

// Function Definitions
#define    CONTROLPILOT_STM32_setHigh()          GPIO_SetBits(CONTROLPILOT_STM32_GPIO_PORT, CONTROLPILOT_STM32_GPIO_PIN)
#define    CONTROLPILOT_STM32_setLow()           GPIO_ResetBits(CONTROLPILOT_STM32_GPIO_PORT, CONTROLPILOT_STM32_GPIO_PIN)

// Function Declarations
void CONTROLPILOT_STM32_configure(void);
void CONTROLPILOT_STM32_timerHighConfig(uint16_t period);
void CONTROLPILOT_STM32_timerHighStart(void);
void CONTROLPILOT_STM32_timerHighStop(void);
void CONTROLPILOT_STM32_timerLowConfig(uint16_t period);
void CONTROLPILOT_STM32_timerLowStart(void);
void CONTROLPILOT_STM32_timerLowStop(void);
void CONTROLPILOT_STM32_timerLowChangeFrequency(uint16_t period);
void CONTROLPILOT_STM32_setDutyCycle(double dutyCycle);