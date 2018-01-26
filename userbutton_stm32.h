// USERBUTTON_STM32 library: This library shall enable three push-buttons for an STM32F0 chip.
// This library also handles the increase and decrease of charging current, as well as the setup
// mode to change the preset maximum value in the FLASH ROM.

// GPIO Definitions
#define    USERBUTTON_GPIO_PORT          GPIOA
#define    USERBUTTON_GPIO_UP_PIN        GPIO_Pin_1
#define    USERBUTTON_GPIO_ENTER_PIN     GPIO_Pin_2
#define    USERBUTTON_GPIO_DOWN_PIN      GPIO_Pin_4
#define    USERBUTTON_GPIO_PERIPH        RCC_AHBPeriph_GPIOA

// EXTI Definitions
#define    USERBUTTON_EXTI_PORTSRC       EXTI_PortSourceGPIOA
#define    USERBUTTON_EXTI_UP_PINSRC     EXTI_PinSource1
#define    USERBUTTON_EXTI_UP_LINE       EXTI_Line1
#define    USERBUTTON_EXTI_ENTER_PINSRC  EXTI_PinSource2
#define    USERBUTTON_EXTI_ENTER_LINE    EXTI_Line2
#define    USERBUTTON_EXTI_DOWN_PINSRC   EXTI_PinSource4
#define    USERBUTTON_EXTI_DOWN_LINE     EXTI_Line4
#define    USERBUTTON_EXTI_PERIPH        RCC_APB2Periph_SYSCFG
#define    USERBUTTON_EXTI_MODE          EXTI_Mode_Interrupt
#define    USERBUTTON_EXTI_TRIGGER       EXTI_Trigger_Rising
#define    USERBUTTON_EXTI_TRIGGER_SETUP EXTI_Trigger_Rising_Falling

// NVIC Definitions
#define    USERBUTTON_NVIC_UP_CHA        EXTI0_1_IRQn
#define    USERBUTTON_NVIC_ENTER_CHA     EXTI2_3_IRQn
#define    USERBUTTON_NVIC_DOWN_CHA      EXTI4_15_IRQn
#define    USERBUTTON_NVIC_PRIORITY      0x03

// Type Definitions
#ifndef BOOLEAN_H
#define BOOLEAN_H
typedef enum {FALSE = 0, TRUE = 1} Boolean;
#endif /* BOOLEAN_H */

// Variable Declarations


// Function Declarations
void USERBUTTON_STM32_configureInterface(void);
void USERBUTTON_STM32_initInterruptUP(void);
void USERBUTTON_STM32_initInterruptENTER(void);
void USERBUTTON_STM32_initInterruptDOWN(void);
void USERBUTTON_STM32_updateAmpSetting(int8_t ampChange);
void USERBUTTON_STM32_initTIM3(void);
void USERBUTTON_STM32_startTIM3(void);
void USERBUTTON_STM32_stopTIM3(void);