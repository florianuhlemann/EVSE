#include "stm32f0xx.h"
#include "stm32f0xx_adc.h"
#include "controlpilot_stm32.h"
#include "helper_stm32.h"
//#include "usart_stm32_console.h"
#include "oled_stm32_ssd1306.h"
#include <stdlib.h>

uint16_t valueOne = 0;
uint16_t valueTwo = 0;
uint16_t valueThree = 0;


void CONTROLPILOT_STM32_configure(void) {

	// Configure GPIO
    RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_IN_PERIPH, ENABLE);
    RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_OUT_PERIPH, ENABLE); //RCC_AHBPeriphClockCmd(CONTROLPILOT_STM32_GPIO_CTCTR_PERIPH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = CONTROLPILOT_STM32_GPIO_CTCTR_PIN;
    GPIO_Init(CONTROLPILOT_STM32_GPIO_CTCTR_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
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
    //USART_STM32_sendIntegerToUSART("ADC Calibration Factor = ", calibrationFactor);
    ADC_Cmd(CONTROLPILOT_STM32_ADC, ENABLE);

    // Wait until ADC is ready
    while (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_ADRDY) != SET) {}
    while (ADC_GetFlagStatus(CONTROLPILOT_STM32_ADC, ADC_FLAG_ADEN) != SET) {}

    // Configure Timers
    RCC_GetClocksFreq(&RCC_Clocks);
    CONTROLPILOT_STM32_timerHighConfig(CONTROLPILOT_STM32_TIMER_HIGH_PERIOD);
    CONTROLPILOT_STM32_timerLowConfig(CONTROLPILOT_STM32_TIMER_LOW_PERIOD);
    CONTROLPILOT_STM32_timerHighStart();

    // Variable Initialization
    CONTROLPILOT_STM32_EVSE_ACTIVE_MODE = DISCONNECTED;
    CONTROLPILOT_STM32_EVSE_REQUESTED_MODE = DISCONNECTED;
    CONTROLPILOT_STM32_CP_VOLTAGE_LOW = 0;
    CONTROLPILOT_STM32_CP_VOLTAGE_HIGH = 0;
    CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = INACTIVE;
    CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
    adcDelayCounterHigh = 0;
    adcDelayCounterLow = 0;

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


void CONTROLPILOT_STM32_startADCConversion(CONTROLPILOT_STM32_EVSE_SIDE activeSide) {

    // Variable Init
    double ADCraw;

    // ADC Data Acquisition Loop
    ADC1->CR |= ADC_CR_ADSTART;
    int i = 0;
    while ((ADC1->ISR & ADC_ISR_EOSEQ) != 8) {
        while ((ADC1->ISR & ADC_ISR_EOC) != 4) {}
        ADC_raw[i] = ADC1->DR;
        i++;
    }
    ADC1->ISR |= ADC_ISR_EOSEQ;

    // Vdd calculation
    ADCraw = (double)ADC_raw[2];
    double Vrefint_cal_float = (double)(*VREFINT_CAL_ADDRPTR);
    double Vddfloat = 3300.0 * Vrefint_cal_float / ADCraw;

    // EVSE_IN calculation
    ADCraw = (double)ADC_raw[0];
    double EVSEvoltage = Vddfloat * ADCraw / 4095.0;
    if (activeSide == HIGH) {
        CONTROLPILOT_STM32_CP_VOLTAGE_HIGH = (uint16_t)EVSEvoltage;
    } else {
        CONTROLPILOT_STM32_CP_VOLTAGE_LOW = (uint16_t)EVSEvoltage;
    }

    // Temp calculation; reduced to Vsense to lower workload on this function
    ADCraw = (double)ADC_raw[1];
    double VsenseCurrent = Vddfloat * ADCraw / 4095.0;    
    HELPER_STM32_setCurrentTemp(VsenseCurrent);

}


void CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(CONTROLPILOT_STM32_EVSE_MODE vehicleMode) {

    if (CONTROLPILOT_STM32_EVSE_ACTIVE_MODE != FAULT) {
        switch (vehicleMode) {
            case DISCONNECTED:
                CONTROLPILOT_STM32_contactorOff();
                break;
            case CONNECTED_NO_PWM:
                CONTROLPILOT_STM32_contactorOff();
                break;
            case CONNECTED:
                CONTROLPILOT_STM32_contactorOff();
                break;
            case CHARGING:
                if (CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER > CONTROLPILOT_STM32_MODE_DELAY) {
                    CONTROLPILOT_STM32_contactorOn();
                } else {
                    CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER++;
                }
                break;
            case CHARGING_COOLED:
                CONTROLPILOT_STM32_contactorOff();
                break;
            case FAULT:
                CONTROLPILOT_STM32_contactorOff();
                CONTROLPILOT_STM32_EVSE_ACTIVE_MODE = FAULT;
                CONTROLPILOT_STM32_timerLowStop();
                CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
                break;
        }
        HELPER_STM32_setCurrentStatus(vehicleMode);
    }

}


void CONTROLPILOT_STM32_setChargingCurrent(uint8_t ampereValue) {

    double ampereValueFloat = (double)ampereValue;
    double trueDutyCycleFloat = ampereValueFloat * 10.0 / 0.6;
    double calibratedDutyCycleFloat = (trueDutyCycleFloat * 0.9795 + 5.1305);
    uint16_t calibratedDutyCycle = (uint16_t)calibratedDutyCycleFloat;
    TIM_SetAutoreload(CONTROLPILOT_STM32_TIMER_LOW, calibratedDutyCycle);
    //USART_STM32_sendIntegerToUSART("calibratedDutyCycle = ", calibratedDutyCycle);

}


void TIM14_IRQHandler(void) {

    if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
        HELPER_STM32_setNeedsUpdate(1);
        /* DEBUG VIEW
        OLED_STM32_clearDisplay();
        OLED_STM32_drawLine(0,9,127,9);
        char maxAmpStr[4] = "   ";
        if (HELPER_STM32_getMaximumAmpere() < 10) {
            maxAmpStr[0] = HELPER_STM32_getMaximumAmpere() + 48;
            maxAmpStr[1] = 0x41; //A
        } else {
            maxAmpStr[0] = HELPER_STM32_getMaximumAmpere() / 10 + 48;
            maxAmpStr[1] = HELPER_STM32_getMaximumAmpere() % 10 + 48;
            maxAmpStr[2] = 0x41; //A
        }
        OLED_STM32_drawMonospaceString(0,0,maxAmpStr);
        uint8_t offsetValue = 0;
        switch (HELPER_STM32_getCurrentStatus()) {
            case DISCONNECTED: offsetValue = 37; OLED_STM32_drawMonospaceString(48+offsetValue, 0, "Getrennt"); break;
            case CONNECTED_NO_PWM: offsetValue = 29; OLED_STM32_drawMonospaceString(48+offsetValue,0,"Verbunden"); break;
            case CONNECTED: offsetValue = 29; OLED_STM32_drawMonospaceString(48+offsetValue,0,"Verbunden"); break;
            case CHARGING: offsetValue = 16; OLED_STM32_drawMonospaceString(48+offsetValue,0,"Ladevorgang"); break;
            case CHARGING_COOLED: offsetValue = 44; OLED_STM32_drawMonospaceString(48+offsetValue,0,"K\xfchlung"); break;
            case FAULT: offsetValue = 11; OLED_STM32_drawMonospaceString(48+offsetValue,0,"Fehlermeldung"); break;
        }
        char buffer[8];
        itoa(CONTROLPILOT_STM32_CP_VOLTAGE_HIGH, buffer,10);
        OLED_STM32_drawMonospaceString(0,11,"CP_VLT_HIGH = ");
        OLED_STM32_drawMonospaceString(78,11,buffer);
        itoa(CONTROLPILOT_STM32_CP_VOLTAGE_LOW, buffer,10);
        OLED_STM32_drawMonospaceString(0,20,"CP_VLT_LOW  = ");
        OLED_STM32_drawMonospaceString(78,20,buffer);
        //itoa(CONTROLPILOT_STM32_TEMP_10X, buffer,10);
        //OLED_STM32_drawMonospaceString(0,29,"TEMP_10X  = ");
        //OLED_STM32_drawMonospaceString(78,29,buffer);
        OLED_STM32_updateDisplay();
        */
    }

}


// Interrupt Routine for HIGH Timer
void TIM16_IRQHandler(void) {

    if (TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_HIGH, TIM_IT_Update);
        CONTROLPILOT_STM32_setHigh();
        if (CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE != INACTIVE && CONTROLPILOT_STM32_EVSE_ACTIVE_MODE != FAULT) {
            CONTROLPILOT_STM32_timerLowStart();
        }
        if (adcDelayCounterHigh > CONTROLPILOT_STM32_ADC_DELAY) {
            CONTROLPILOT_STM32_startADCConversion(HIGH);
            adcDelayCounterHigh = 0;
        } else {
            adcDelayCounterHigh++;
        }

        if (CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE != ACTIVE) {
            CONTROLPILOT_STM32_CP_VOLTAGE_HIGH = CONTROLPILOT_STM32_CP_VOLTAGE_HIGH - CONTROLPILOT_STM32_ADC_PWM_CORRECTOR;
        }

        switch (CONTROLPILOT_STM32_CP_VOLTAGE_HIGH) {
            case 2952 ... 3200:
                CONTROLPILOT_STM32_EVSE_ACTIVE_MODE = DISCONNECTED;
                CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(DISCONNECTED);
                CONTROLPILOT_STM32_timerLowStop();
                CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = INACTIVE;
                CONTROLPILOT_STM32_CP_VOLTAGE_LOW = 0;
                CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
                break;
            case 2582 ... 2830:
                if (CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE == INACTIVE) {
                    CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = ACTIVE;
                    CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(CONNECTED_NO_PWM);
                } else {
                    CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(CONNECTED);
                }
                CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
                break;
            case 2212 ... 2459:
                if (CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE == INACTIVE) {
                    CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = ACTIVE;
                }
                CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(CHARGING);
                break;
            case 1841 ... 2089:
                if (CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE == INACTIVE) {
                    CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = ACTIVE;
                }
                CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(CHARGING_COOLED);
                CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
                break;
            default:
                CONTROLPILOT_STM32_timerLowStop();
                CONTROLPILOT_STM32_EVSE_ACTIVE_PWM_STATE = INACTIVE;
                CONTROLPILOT_STM32_CP_VOLTAGE_LOW = 0;
                CONTROLPILOT_STM32_EVSE_MODE_SWITCH_COUNTER = 0;
                break;
        }





    }

}


// LOW Interrupt Routine
// This function reads the low voltage of the PWM signal and triggers
// a FAULT state if the voltage is less negative than expected.
void TIM17_IRQHandler(void) {

    if (TIM_GetITStatus(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(CONTROLPILOT_STM32_TIMER_LOW, TIM_IT_Update);
        CONTROLPILOT_STM32_setLow();
        CONTROLPILOT_STM32_startADCConversion(LOW);
        if (CONTROLPILOT_STM32_CP_VOLTAGE_LOW > 150) { CONTROLPILOT_STM32_SWITCH_VEHICLE_STATUS(FAULT); }

	}

}

