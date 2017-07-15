#include "stm32f0xx.h"
#include "controlpilot_stm32.h"
#include "helper_stm32.h"

RCC_ClocksTypeDef RCC_Clocks;

void CONTROLPILOT_STM32_configure(void) {

	// Configure GPIO
	RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_PERIPH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CONTROLPILOT_STM32_GPIO_PORT, &GPIO_InitStructure);

	// Configure Timers
	RCC_GetClocksFreq(&RCC_Clocks);
	CONTROLPILOT_STM32_timerHighConfig(CONTROLPILOT_STM32_TIMER_HIGH_PERIOD);
	CONTROLPILOT_STM32_timerLowConfig(CONTROLPILOT_STM32_TIMER_LOW_PERIOD);
	CONTROLPILOT_STM32_timerHighStart();
	delayMilliseconds(5000);
	CONTROLPILOT_STM32_timerLowChangeFrequency(480);

}


void CONTROLPILOT_STM32_timerHighConfig(uint16_t period) {

	// Configure Timer
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t APB1_PrescalerValue;
	uint32_t TIM_PeriodValue = period;
    RCC_APB1PeriphClockCmd(CONTROLPILOT_STM32_TIMER_HIGH_PERIPH, ENABLE);
    APB1_PrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = APB1_PrescalerValue;
    TIM_TimeBaseStructure.TIM_Period = TIM_PeriodValue;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(CONTROLPILOT_STM32_TIMER_HIGH, &TIM_TimeBaseStructure);

    // Configure NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_TIMER_HIGH_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_TIMER_HIGH_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Initialize Timer
    TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);

}


void CONTROLPILOT_STM32_timerLowConfig(uint16_t period) {

	// Configure Timer
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t APB1_PrescalerValue;
	uint32_t TIM_PeriodValue = period;
    RCC_APB1PeriphClockCmd(CONTROLPILOT_STM32_TIMER_LOW_PERIPH, ENABLE);
    APB1_PrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = APB1_PrescalerValue;
    TIM_TimeBaseStructure.TIM_Period = TIM_PeriodValue;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(CONTROLPILOT_STM32_TIMER_LOW, &TIM_TimeBaseStructure);

    // Configure NVIC
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_TIMER_LOW_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_TIMER_LOW_PRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Initialize Timer
    TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);

}

void CONTROLPILOT_STM32_timerLowChangeFrequency(uint16_t period) {

	// Reconfigure Timer
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	uint16_t APB1_PrescalerValue;
	uint32_t TIM_PeriodValue = period;
    RCC_APB1PeriphClockCmd(CONTROLPILOT_STM32_TIMER_LOW_PERIPH, ENABLE);
    APB1_PrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000000) - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = APB1_PrescalerValue;
    TIM_TimeBaseStructure.TIM_Period = TIM_PeriodValue;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(CONTROLPILOT_STM32_TIMER_LOW, &TIM_TimeBaseStructure);

    // Reinitialize Timer
    TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);

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


void TIM2_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);
        CONTROLPILOT_STM32_timerLowStart();
		CONTROLPILOT_STM32_setHigh();
    }

}


void TIM3_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);
        CONTROLPILOT_STM32_timerLowStop();
		CONTROLPILOT_STM32_setLow();
	}

}