#include "stm32f0xx.h"
#include "helper_stm32.h"

void delayMilliseconds (int milliseconds) {
	uint64_t counter = 2091 * milliseconds;
	while (counter > 0) {
		counter--;
	}
}


void createDisplayBuffer(void) {
	for (int i=0; i<512;i++) {
		OLED_STM32_displayBuffer[i] = 0xAD;
	}
}