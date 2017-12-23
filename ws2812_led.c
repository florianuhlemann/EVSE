#include "stm32f0xx.h"
#include "ws2812_led.h"
#include "helper_stm32.h"
#include <math.h>

uint8_t colorArray[WS2812_NUM_LEDS][3];

void WS2812_STM32_init(void) {

	// Enabling Clocks
	RCC_AHBPeriphClockCmd(WS2812_RCC_PERIPH, ENABLE);

	// Configuring GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = WS2812_GPIO_SPEED;
	GPIO_InitStructure.GPIO_Pin = WS2812_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WS2812_GPIO_PORT, &GPIO_InitStructure);

	// Initialize Color Arrays
	for (int i = 0; i < WS2812_NUM_LEDS; i++) {
		for (int j = 0; j < 3; j++) {
			colorArray[i][j] = 0;
		}
	}

}

void WS2812_STM32_setRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue) {

	colorArray[id][0] = green;
	colorArray[id][1] = red;
	colorArray[id][2] = blue;

}

void WS2812_STM32_sendToLED(void) {

	// Variable Definition
	int binaryCounter = 0;
	int maxNumber = WS2812_NUM_LEDS * 8 * 3;
	uint8_t delayCounter = 0;
	BitAction dataArray[maxNumber];

	// Creating dataArray for SPI Transmission
	for (int h = 0; h < WS2812_NUM_LEDS; h++) {
		for (int i = 0; i < 3; i++) {
	        for (int j = 7; j >= 0; j--) {
	            int divisor = (int) pow(2.0,j);
	            dataArray[binaryCounter] = (BitAction) ((colorArray[h][i] & (1<<j)) / divisor);
	            binaryCounter++;
	        }
    	}
	}

	// Sending dataArray
	for (int i = 0; i < maxNumber; i++) { // total of 1210µs clock
		WS2812_GPIO_PORT->BSRR = GPIO_Pin_7; //Set High!
		if (dataArray[i]) {
			delayCounter++;
			uint8_t jk = 0;
			GPIOA->BRR = GPIO_Pin_7; //Set Low!
		} else {
			uint16_t jk = 0;
			GPIOA->BRR = GPIO_Pin_7; //Set Low!
			delayCounter++;
		}
	}
	/*
	for (int i = 0; i < maxNumber; i++) { // total of 1500µs clock
		WS2812_GPIO_PORT->BSRR = WS2812_MOSI_PIN; //Set High!
		if (dataArray[i]) {
			int jk = 0;
			delayCounter++;
			delayCounter++;
			WS2812_GPIO_PORT->BRR = WS2812_MOSI_PIN; //Set Low!
		} else {
			uint16_t jk = 0;
			WS2812_GPIO_PORT->BRR = WS2812_MOSI_PIN; //Set Low!
			delayCounter++;
			delayCounter++;
		}
	}
	*/
	/*
	for (int i = 0; i < maxNumber; i++) { // total of 2500µs clock
		WS2812_GPIO_PORT->BSRR = WS2812_MOSI_PIN; //Set High!
		if (dataArray[i]) {
			delayCounter++;
			delayCounter++;
			delayCounter++;
			delayCounter++;
			delayCounter++;
			uint16_t jk = 0;
			WS2812_GPIO_PORT->BRR = WS2812_MOSI_PIN; //Set Low!
		} else {
			uint16_t jk = 0;
			WS2812_GPIO_PORT->BRR = WS2812_MOSI_PIN; //Set Low!
			delayCounter++;
			delayCounter++;
			delayCounter++;
			delayCounter++;
			delayCounter++;
		}
	}
	*/
	WS2812_GPIO_PORT->BRR = WS2812_MOSI_PIN;
	//delayMilliseconds(1);

}
	


