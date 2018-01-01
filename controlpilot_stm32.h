// CONTROLPILOT_STM32 library: This library shall enable the J1772 Control Pilot Signal on an STM32F0 chip.

// Type Definitions
#ifndef EVSEMODE_H
#define EVSEMODE_H
typedef enum { DISCONNECTED = 0, CONNECTED_NO_PWM = 1, CONNECTED = 2, CHARGING = 3, CHARGING_COOLED = 4, FAULT = 5 } CONTROLPILOT_STM32_EVSE_MODE;
#endif /* EVSEMODE_H */
typedef enum {          LOW = 0,             HIGH = 1 }                                                              CONTROLPILOT_STM32_EVSE_SIDE;
typedef enum {     INACTIVE = 0,           ACTIVE = 1 }                                                              CONTROLPILOT_STM32_STATE;

// GPIO Definitions
#define    CONTROLPILOT_STM32_GPIO_IN_PERIPH     RCC_AHBPeriph_GPIOA
#define    CONTROLPILOT_STM32_GPIO_OUT_PERIPH    RCC_AHBPeriph_GPIOF
#define    CONTROLPILOT_STM32_GPIO_CTCTR_PERIPH  RCC_AHBPeriph_GPIOF
#define    CONTROLPILOT_STM32_GPIO_IN_PORT       GPIOA
#define    CONTROLPILOT_STM32_GPIO_OUT_PORT      GPIOF
#define    CONTROLPILOT_STM32_GPIO_CTCTR_PORT    GPIOF
#define    CONTROLPILOT_STM32_GPIO_IN_PIN        GPIO_Pin_6
#define    CONTROLPILOT_STM32_GPIO_OUT_PIN       GPIO_Pin_0
#define    CONTROLPILOT_STM32_GPIO_CTCTR_PIN     GPIO_Pin_1

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
#define    CONTROLPILOT_STM32_ADC_SAMPLETIME     ADC_SampleTime_55_5Cycles
#define    CONTROLPILOT_STM32_ADC_PWM_CORRECTOR  60

// Constants Definitions
#define    CONTROLPILOT_STM32_TIMER_HIGH_PERIOD  1021
#define    CONTROLPILOT_STM32_TIMER_LOW_PERIOD   539
#define    VREFINT_CAL_ADDR                      ((uint16_t*) ((uint32_t) 0x1ffff7ba))
#define    CONTROLPILOT_STM32_ADC_DELAY          2
#define    CONTROLPILOT_STM32_MODE_DELAY         25

// Variable Definitions
RCC_ClocksTypeDef                                RCC_Clocks;
uint16_t                                         ADC_raw[3];
uint8_t                                          adcDelayCounterHigh;
uint8_t                                          adcDelayCounterLow;
CONTROLPILOT_STM32_EVSE_MODE                     CONTROLPILOT_STM32_EVSE_ACTIVE_MODE;
CONTROLPILOT_STM32_EVSE_MODE                     CONTROLPILOT_STM32_EVSE_REQUESTED_MODE;
CONTROLPILOT_STM32_STATE                         CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE;
CONTROLPILOT_STM32_STATE                         CONTROLPILOT_STM32_EVSE_ACTIVE_FAULT_STATE;
uint16_t                                         CONTROLPILOT_STM32_CP_VOLTAGE_LOW;
uint16_t                                         CONTROLPILOT_STM32_CP_VOLTAGE_HIGH;
uint8_t                                          CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER;

// Function Definitions
#define    CONTROLPILOT_STM32_setHigh()          GPIO_SetBits(CONTROLPILOT_STM32_GPIO_OUT_PORT, CONTROLPILOT_STM32_GPIO_OUT_PIN)
#define    CONTROLPILOT_STM32_setLow()           GPIO_ResetBits(CONTROLPILOT_STM32_GPIO_OUT_PORT, CONTROLPILOT_STM32_GPIO_OUT_PIN)
#define    CONTROLPILOT_STM32_contactorOn()      GPIO_SetBits(CONTROLPILOT_STM32_GPIO_CTCTR_PORT, CONTROLPILOT_STM32_GPIO_CTCTR_PIN)
#define    CONTROLPILOT_STM32_contactorOff()     GPIO_ResetBits(CONTROLPILOT_STM32_GPIO_CTCTR_PORT, CONTROLPILOT_STM32_GPIO_CTCTR_PIN)

// Function Declarations
void CONTROLPILOT_STM32_configure(void);
void CONTROLPILOT_STM32_timerHighConfig(uint16_t period);
void CONTROLPILOT_STM32_timerHighStart(void);
void CONTROLPILOT_STM32_timerHighStop(void);
void CONTROLPILOT_STM32_timerLowConfig(uint16_t period);
void CONTROLPILOT_STM32_timerLowStart(void);
void CONTROLPILOT_STM32_timerLowStop(void);
void CONTROLPILOT_STM32_startADCConversion(CONTROLPILOT_STM32_EVSE_SIDE activeSide);
void CONTROLPILOT_STM32_setChargingCurrent(uint8_t ampereValue);

// Debug Delcarations
void CONTROLPILOT_STM32_timerThreeConfig(uint16_t period);
void CONTROLPILOT_STM32_timerThreeStart(void);
void CONTROLPILOT_STM32_timerThreeStop(void);