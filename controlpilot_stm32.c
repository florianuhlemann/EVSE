#include "stm32f0xx.h"
#include "stm32f0xx_adc.h"
#include "controlpilot_stm32.h"
#include "helper_stm32.h"
#include "usart_stm32_console.h"

RCC_ClocksTypeDef RCC_Clocks;
uint16_t idx = 0;
uint16_t ADC_raw[3];
VehicleConnect vehicleStatus = DISCONNECTED;
uint16_t myValueOne = 0;
uint16_t myValueTwo = 0;
uint16_t myValueThree = 0;
uint32_t successfulChangeCounter = 0;

uint16_t EOC_Counter = 0;
uint16_t EOSEQ_Counter = 0;

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


    // Configure ADC
    RCC_APB2PeriphClockCmd(CONTROLPILOT_STM32_ADC_PERIPH, ENABLE);
    ADC_InitTypeDef ADC_InitStructure;
    ADC_StructInit(&ADC_InitStructure);
    ADC_Init(CONTROLPILOT_STM32_ADC, &ADC_InitStructure);

    // Activate Temperature Sensore and Internal Reference Voltage Sensor
    ADC_TempSensorCmd(ENABLE);
    ADC_VrefintCmd(ENABLE);

    // Activate Channels
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_EVSE, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_TEMP, CONTROLPILOT_STM32_ADC_SAMPLETIME);
    ADC_ChannelConfig(CONTROLPILOT_STM32_ADC, CONTROLPILOT_STM32_ADC_CHANNEL_VREF, CONTROLPILOT_STM32_ADC_SAMPLETIME);

    // Start calibration, then wait until completed, then enable ADC
    uint16_t calibrationFactor = (uint16_t)ADC_GetCalibrationFactor(CONTROLPILOT_STM32_ADC);
    USART_STM32_sendIntegerToUSART("ADC Calibration Factor = ", calibrationFactor);
    ADC_Cmd(CONTROLPILOT_STM32_ADC, ENABLE);

    // Configure Interrupts
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = CONTROLPILOT_STM32_ADC_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPriority = CONTROLPILOT_STM32_ADC_IRQ_PRIO;
    NVIC_Init(&NVIC_InitStructure);

    // Activate ADC Interrupts for End of Conversion, End of Sequence
    ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC);
    ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ);
    ADC_ITConfig(CONTROLPILOT_STM32_ADC, ADC_IT_EOC, ENABLE);
    ADC_ITConfig(CONTROLPILOT_STM32_ADC, ADC_IT_EOSEQ, ENABLE);
    ADC_ITConfig(CONTROLPILOT_STM32_ADC, ADC_IT_OVR, ENABLE);


    // Wait until ADC is ready
    while (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_ADRDY) != SET) {}
    while (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_ADEN) != SET) {}

    // Configure Timers
    RCC_GetClocksFreq(&RCC_Clocks);
    CONTROLPILOT_STM32_timerHighConfig(CONTROLPILOT_STM32_TIMER_HIGH_PERIOD);
    CONTROLPILOT_STM32_timerLowConfig(CONTROLPILOT_STM32_TIMER_LOW_PERIOD);
    CONTROLPILOT_STM32_timerHighStart();


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
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x04;
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


void CONTROLPILOT_STM32_timerThreeStop(void) {

    TIM_ITConfig(TIM14, TIM_IT_Update, DISABLE);
    TIM_Cmd(TIM14, DISABLE);

}


void CONTROLPILOT_STM32_getInputVoltage(void) {
    USART_STM32_sendIntegerToUSART("myValueOne   = ", myValueOne);
    USART_STM32_sendIntegerToUSART("myValueTwo   = ", myValueTwo);
    USART_STM32_sendIntegerToUSART("myValueThree = ", myValueThree);
    USART_STM32_sendIntegerToUSART("EOC_Counter = ", EOC_Counter);
    EOC_Counter = 0;
    USART_STM32_sendIntegerToUSART("EOSEQ_Counter = ", EOSEQ_Counter);
    EOSEQ_Counter = 0;
    //vehicleStatus = DISCONNECTED;
}


void CONTROLPILOT_STM32_startADCConversion(void) {
    if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC) != RESET) {
        if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC) != RESET) {
            ADC_StartOfConversion(CONTROLPILOT_STM32_ADC);
        }
    }
}


void TIM14_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(TIM14, TIM_IT_Update)) {
        TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
        CONTROLPILOT_STM32_startADCConversion();
        CONTROLPILOT_STM32_getInputVoltage();
    }

}


void TIM16_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);
        if (vehicleStatus != DISCONNECTED) { CONTROLPILOT_STM32_timerLowStart(); }
        CONTROLPILOT_STM32_setHigh();
        //CONTROLPILOT_STM32_startADCConversion();
        if ((myValueOne > 2895) && (myValueOne < 2995)) {
            successfulChangeCounter++;
        }
        if (successfulChangeCounter == 5000) {
            successfulChangeCounter = 0;
            vehicleStatus = CONNECTED;
            USART_STM32_sendStringToUSART("EVSE: Vehicle connected. PWM started.");
        }

    }

}


void TIM17_IRQHandler(void) {

    if (RESET != TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update)) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);
        CONTROLPILOT_STM32_timerLowStop();
		CONTROLPILOT_STM32_setLow();
	}

}


#define IT_STATUS_MODE
//#define FLAG_STATUS_MODE

void ADC1_IRQHandler(void) {

    #ifdef IT_STATUS_MODE
    if (ADC_GetITStatus(CONTROLPILOT_STM32_ADC, ADC_IT_EOC) != RESET) {
        ADC_ClearITPendingBit(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC);
        ADC_raw[idx] = ADC_GetConversionValue(CONTROLPILOT_STM32_ADC);
        ADC_raw[idx] = ADC_GetConversionValue(CONTROLPILOT_STM32_ADC);
        ADC_raw[idx] = ADC_GetConversionValue(CONTROLPILOT_STM32_ADC);
        idx++;
        EOC_Counter++;
    }

    if (ADC_GetITStatus(CONTROLPILOT_STM32_ADC, ADC_IT_EOSEQ) != RESET) {
        ADC_ClearITPendingBit(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ);
        myValueOne = ADC_raw[0];
        myValueTwo = ADC_raw[1];
        myValueThree = ADC_raw[2];
        idx = 0;
        EOSEQ_Counter++;
    }
    if (ADC_GetITStatus(CONTROLPILOT_STM32_ADC, ADC_IT_OVR) != RESET) {
        ADC_ClearITPendingBit(CONTROLPILOT_STM32_ADC, ADC_IT_OVR);
        USART_STM32_sendStringToUSART("OVERRUN DETECTED");
    }
    #endif

    #ifdef FLAG_STATUS_MODE
    if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC) != RESET) {
        ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOC);
        ADC_raw[idx] = ADC_GetConversionValue(CONTROLPILOT_STM32_ADC);
        idx++;
        EOC_Counter++;
    }

    if (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ) != RESET) {
        ADC_ClearFlag(CONTROLPILOT_STM32_ADC, ADC_FLAG_EOSEQ);
        myValueOne = ADC_raw[0];
        myValueTwo = ADC_raw[1];
        myValueThree = ADC_raw[2];
        idx = 0;
        EOSEQ_Counter++;
    }
    #endif

}


void testADEN(void) {
    if (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)) {
        USART_STM32_sendStringToUSART("ADC_FLAG_ADEN = 1");
    } else {
        USART_STM32_sendStringToUSART("ADC_FLAG_ADEN = 0");
    }
}

