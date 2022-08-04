/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "wifi.h"

int main (void)
{
	/* Insert system clock initialization codeh ere (sysclk_init()). */

	sysclk_init();
	wdt_disable(WDT);
	board_init();
	
	configure_usart_wifi();

	while(1){
		delay_ms(500);
		usart_write_line(WIFI_USART, "Hello\r\n");
	}
}
