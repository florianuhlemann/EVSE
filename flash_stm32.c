#include "stm32f0xx.h"
#include "flash_stm32.h"
//#include "usart_stm32_console.h"

// A self-reset feature of the electronic would be nice to allow the device to reboot after changing the maximum ampere setting in the flash.

void FLASH_STM32_setNewMaximumAmpere(uint8_t newValue) {
	FLASH_Unlock();
	FLASH_Status eraseResponse = FLASH_ErasePage(MAXIMUM_AMPERE_ADDRESS);
	if (eraseResponse != FLASH_COMPLETE) {
		//USART_STM32_sendStringToUSART("DEBUG: Could not erase memory page from flash memory for MAXIMUM_AMPERE.");
	}
	FLASH_Status flashResponse = FLASH_ProgramWord(MAXIMUM_AMPERE_ADDRESS, newValue);
	if (flashResponse != FLASH_COMPLETE) {
		//USART_STM32_sendStringToUSART("DEBUG: Could not write new MAXIMUM_AMPERE value to flash memory.");
	}
	FLASH_Lock();
	//USART_STM32_sendStringToUSART("A new MAXIMUM_AMPERE value has been flashed. Please restart the device to take effect.");
}

uint8_t FLASH_STM32_getMaximumAmpere(void) {

	return (uint8_t)(*MAXIMUM_AMPERE_ADDRPTR);;

}
