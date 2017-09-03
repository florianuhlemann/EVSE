// CONTROLPILOT_STM32 library: This library shall enable the J1772 Control Pilot Signal on an STM32F0 chip.

// Type Definitions
typedef enum { DISCONNECTED = 0, CONNECTED } VehicleConnect;

// GPIO Definitions
#define    CONTROLPILOT_STM32_GPIO_IN_PERIPH     RCC_AHBPeriph_GPIOA
#define    CONTROLPILOT_STM32_GPIO_OUT_PERIPH    RCC_AHBPeriph_GPIOF
#define    CONTROLPILOT_STM32_GPIO_IN_PORT       GPIOA
#define    CONTROLPILOT_STM32_GPIO_OUT_PORT      GPIOF
#define    CONTROLPILOT_STM32_GPIO_IN_PIN        GPIO_Pin_6
#define    CONTROLPILOT_STM32_GPIO_OUT_PIN       GPIO_Pin_0

// TIM Definitions
#define    CONTROLPILOT_STM32_TIMER_HIGH         TIM16
#define    CONTROLPILOT_STM32_TIMER_LOW          TIM17
#define    CONTROLPILOT_STM32_TIMER_HIGH_PRIO    0x02
#define    CONTROLPILOT_STM32_TIMER_LOW_PRIO     0x02
#define    CONTROLPILOT_STM32_TIMER_HIGH_IRQ     TIM16_IRQn
#define    CONTROLPILOT_STM32_TIMER_LOW_IRQ      TIM17_IRQn
#define    CONTROLPILOT_STM32_TIMER_HIGH_PERIPH  RCC_APB2Periph_TIM16
#define    CONTROLPILOT_STM32_TIMER_LOW_PERIPH   RCC_APB2Periph_TIM17

// ADC Definitions
#define    CONTROLPILOT_STM32_ADC                ADC1
#define    CONTROLPILOT_STM32_ADC_PERIPH         RCC_APB2Periph_ADC1
#define    CONTROLPILOT_STM32_ADC_IRQ            ADC1_IRQn
#define    CONTROLPILOT_STM32_ADC_IRQ_PRIO       0x03
#define    CONTROLPILOT_STM32_ADC_CHANNEL_EVSE   ADC_Channel_6
#define    CONTROLPILOT_STM32_ADC_CHANNEL_TEMP   ADC_Channel_TempSensor
#define    CONTROLPILOT_STM32_ADC_CHANNEL_VREF   ADC_Channel_Vrefint
#define    CONTROLPILOT_STM32_ADC_SAMPLETIME     ADC_SampleTime_1_5Cycles

// Variable Definitions
#define    CONTROLPILOT_STM32_TIMER_HIGH_PERIOD  999
#define    CONTROLPILOT_STM32_TIMER_LOW_PERIOD   500
#define    VREFINT_CAL_ADDR                      ((uint16_t*) ((uint32_t) 0x1ffff7ba))

// Function Definitions
#define    CONTROLPILOT_STM32_setHigh()          GPIO_SetBits(CONTROLPILOT_STM32_GPIO_OUT_PORT, CONTROLPILOT_STM32_GPIO_OUT_PIN)
#define    CONTROLPILOT_STM32_setLow()           GPIO_ResetBits(CONTROLPILOT_STM32_GPIO_OUT_PORT, CONTROLPILOT_STM32_GPIO_OUT_PIN)

// Function Declarations
void CONTROLPILOT_STM32_configure(void);
void CONTROLPILOT_STM32_timerHighConfig(uint16_t period);
void CONTROLPILOT_STM32_timerHighStart(void);
void CONTROLPILOT_STM32_timerHighStop(void);
void CONTROLPILOT_STM32_timerLowConfig(uint16_t period);
void CONTROLPILOT_STM32_timerLowStart(void);
void CONTROLPILOT_STM32_timerLowStop(void);
void CONTROLPILOT_STM32_timerLowChangeFrequency(uint16_t period);
void CONTROLPILOT_STM32_startADCConversion(void);

// Debug Delcarations
void CONTROLPILOT_STM32_timerThreeConfig(uint16_t period);
void CONTROLPILOT_STM32_timerThreeStart(void);
void CONTROLPILOT_STM32_timerThreeStop(void);
void testADEN(void);