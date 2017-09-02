#include "stm32f0xx.h"
#include "stm32f0xx_adc.h"
#include "controlpilot_stm32.h"
#include "helper_stm32.h"
#include "usart_stm32_console.h"


RCC_ClocksTypeDef RCC_Clocks;
uint8_t idx = 0;
uint16_t ADC_raw[3];


void CONTROLPILOT_STM32_configure(void) {

	// Configure GPIO
    RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_IN_PERIPH, ENABLE);
	RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_OUT_PERIPH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_OUT_PIN;
	GPIO_Init(CONTROLPILOT_STM32_GPIO_OUT_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_IN_PIN;
    GPIO_Init(CONTROLPILOT_STM32_GPIO_IN_PORT, &GPIO_InitStructure);

	// Configure Timers
	RCC_GetClocksFreq(&RCC_Clocks);
	CONTROLPILOT_STM32_timerHighConfig(CONTROLPILOT_STM32_TIMER_HIGH_PERIOD);
	CONTROLPILOT_STM32_timerLowConfig(CONTROLPILOT_STM32_TIMER_LOW_PERIOD);
	CONTROLPILOT_STM32_timerHighStart();

    // Configure ADC - Channel 6 = PA6 EVSE_IN - Channel 16 = Temperature Sensor - Channel 17 = Vrefint Sensor
    RCC_APB2PeriphClockCmd(CONTROLPILOT_STM32_ADC_PERIPH, ENABLE);
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(CONTROLPILOT_STM32_ADC, &ADC_InitStructure);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_EVSE, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_TEMP, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_TempSensorCmd(ENABLE);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_VREF, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_VrefintCmd(ENABLE);
    ADC_Cmd(CONTROLPILOT_STM32_ADC, ENABLE);

    // Configure Interrupts
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_ADC_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_ADC_IRQ_PRIO;
    NVIC_Init(&NVIC_InitStructure);

    ADC_StartOfConversion(CONTROLPILOT_STM32_ADC); // Needs to be started before ITConfig works.
    ADC_ITConfig(CONTROLPILOT_STM32_ADC, ADC_IT_EOC, ENABLE);
    ADC_ITConfig(CONTROLPILOT_STM32_ADC, ADC_IT_EOSEQ, ENABLE);

    // Start calibration
    // Wait until calibration is completed

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


void CONTROLPILOT_STM32_timerThreeConfig(uint16_t period) {

    //Configure Timer
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    uint16_t myPrescalerValue = (RCC_Clocks.PCLK_Frequency / 1000) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = myPrescalerValue - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

    // Configure NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Initialize Timer
    TIM_ClearITPendingBit(TIM14, TIM_IT_Update);

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


void CONTROLPILOT_STM32_timerThreeStart(void) {

    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM14, 0);
    TIM_Cmd(TIM14, ENABLE);

}


void CONTROLPILOT_STM32_setDutyCycle(double dutyCycle) {

}


void CONTROLPILOT_STM32_getInputVoltage(void) {

}


void TIM14_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(TIM14, TIM_IT_Update)) {
        TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
        ADC_StartOfConversion(CONTROLPILOT_STM32_ADC);
        //STM_EVAL_LEDToggle(LED3);
    }

}


void TIM16_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);
        ADC_StartOfConversion(CONTROLPILOT_STM32_ADC);
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


void ADC1_IRQHandler(void) {

    if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC) != RESET) {
        ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC);
        ADC_raw[idx] = ADC_GetConversionValue(CONTROLPILOT_STM32_ADC);
        uint16_t VddCalibValue = (*VREFINT_CAL_ADDR);
        uint16_t Vdd = 3300 * VddCalibValue / ADC_raw[0];
        //uint16_t Vin = ADC_raw[0] * Vdd / 4095;
        //float VinFloat = (float)(Vin / 10) / 100.0;
        //float VddFloat = (float)(Vdd / 10) / 100.0;
        USART_STM32_sendIntegerToUSART("Varuable Vdd = ", Vdd);
        idx++;
    }
    if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ) != RESET) {
        ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ);
        idx = 0;
        USART_STM32_sendStringToUSART("ADC: End of Sequence triggered.");
    }
}