#include "stm32f0xx.h"
#include "controlpilot_stm32.h"
#include "helper_stm32.h"

RCC_ClocksTypeDef RCC_Clocks;

void CONTROLPILOT_STM32_configure(void) {

	// Configure GPIO
    RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_IN_PERIPH, ENABLE);
	RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_OUT_PERIPH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_OUT_PIN;
	GPIO_Init(CONTROLPILOT_STM32_GPIO_OUT_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_IN_PIN;
    GPIO_Init(CONTROLPILOT_STM32_GPIO_IN_PORT, &GPIO_InitStructure);

	// Configure Timers
	RCC_GetClocksFreq(&RCC_Clocks);
	CONTROLPILOT_STM32_timerHighConfig(CONTROLPILOT_STM32_TIMER_HIGH_PERIOD);
	CONTROLPILOT_STM32_timerLowConfig(CONTROLPILOT_STM32_TIMER_LOW_PERIOD);
	CONTROLPILOT_STM32_timerHighStart();

    // Configure ADC
    RCC_APB2PeriphClockCmd(CONTROLPILOT_STM32_ADC_PERIPH, ENABLE);
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //DISABLE, if manually starting reading before getting value
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(CONTROLPILOT_STM32_ADC, &ADC_InitStructure);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_Cmd(CONTROLPILOT_STM32_ADC, ENABLE);
    ADC_ContinuousModeCmd(CONTROLPILOT_STM32_ADC, ENABLE); // May be possible to disable
    ADC_StartOfConversion(CONTROLPILOT_STM32_ADC); // Use before each read request if disabling continuous mode

}


void CONTROLPILOT_STM32_timerHighConfig(uint16_t period) {

    //Configure Timer
    RCC_APB2PeriphClockCmd(CONTROLPILOT_STM32_TIMER_HIGH_PERIPH, ENABLE);
    uint16_t myPrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000000) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = myPrescalerValue - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(CONTROLPILOT_STM32_TIMER_HIGH, &TIM_TimeBaseStructure);

    // Configure NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_TIMER_HIGH_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_TIMER_HIGH_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Initialize Timer
    TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);

}


void CONTROLPILOT_STM32_timerLowConfig(uint16_t period) {

    //Configure Timer
    RCC_APB2PeriphClockCmd(CONTROLPILOT_STM32_TIMER_LOW_PERIPH, ENABLE);
    uint16_t myPrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000000) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = myPrescalerValue - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(CONTROLPILOT_STM32_TIMER_LOW, &TIM_TimeBaseStructure);

    // Configure NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_TIMER_LOW_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_TIMER_LOW_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Initialize Timer
    TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);

}


void CONTROLPILOT_STM32_timerLowChangeFrequency(uint16_t period) {

    TIM_SetAutoreload(CONTROLPILOT_STM32_TIMER_LOW,period);

}


void CONTROLPILOT_STM32_timerHighStart(void) {

    TIM_ITConfig(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update, ENABLE);
    TIM_SetCounter(CONTROLPILOT_STM32_TIMER_HIGH, 0);
    TIM_Cmd(CONTROLPILOT_STM32_TIMER_HIGH, ENABLE);

}


void CONTROLPILOT_STM32_timerHighStop(void) {

    TIM_ITConfig(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update, DISABLE);
    TIM_Cmd(CONTROLPILOT_STM32_TIMER_HIGH, DISABLE);

}


void CONTROLPILOT_STM32_timerLowStart(void) {

    TIM_ITConfig(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update, ENABLE);
    TIM_SetCounter(CONTROLPILOT_STM32_TIMER_LOW, 0);
    TIM_Cmd(CONTROLPILOT_STM32_TIMER_LOW, ENABLE);

}


void CONTROLPILOT_STM32_timerLowStop(void) {

    TIM_ITConfig(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update, DISABLE);
    TIM_Cmd(CONTROLPILOT_STM32_TIMER_LOW, DISABLE);

}


void CONTROLPILOT_STM32_setDutyCycle(double dutyCycle) {

}


void CONTROLPILOT_STM32_getInputVoltage(void) {

}


void TIM16_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);
        CONTROLPILOT_STM32_timerLowStart();
		CONTROLPILOT_STM32_setHigh();
    }

}


void TIM17_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);
        CONTROLPILOT_STM32_timerLowStop();
		CONTROLPILOT_STM32_setLow();
	}

}