/*
 * wifi.c
 *
 * Created: 2/9/2021 5:15:59 AM
 *  Author: zengl
 */ 

#include "wifi.h"
#include <string.h>

volatile uint32_t recieved_byte_wifi = 0;
volatile uint32_t input_pos_wifi = 0;

void USART_Handler(void){
	uint32_t ul_status;
	
	/* Read USART status. */
	ul_status = usart_get_status(WIFI_USART);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXBUFF) {
		usart_read(WIFI_USART, &recieved_byte_wifi);
		process_incoming_byte_wifi((uint8_t)recieved_byte_wifi);
		
	}
}

static void wifi_command_response_handler(void){
	process_data_wifi();
	for(int ii = 0; ii<1000; ii++){
		input_line_wifi[ii] = 0;
	}
	input_pos_wifi = 0;
}

void configure_usart_wifi(void){
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);

	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);

	/* Configure USART CTS pin */
	gpio_configure_pin(PIN_USART0_CTS_IDX, PIN_USART0_CTS_FLAGS);

	/* Configure USART RTS pin */
	gpio_configure_pin(PIN_USART0_RTS_IDX, PIN_USART0_RTS_FLAGS);
	
	static uint32_t ul_sysclk;
	sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};
	/* Get peripheral clock. */
	ul_sysclk = sysclk_get_peripheral_hz();

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART. */
	usart_init_hw_handshaking(WIFI_USART, &usart_console_settings, ul_sysclk);

	/* Disable all the interrupts. */
	usart_disable_interrupt(WIFI_USART, ALL_INTERRUPT_MASK);
	
	/* Enable TX & RX function. */
	usart_enable_tx(WIFI_USART);
	usart_enable_rx(WIFI_USART);
	
	usart_enable_interrupt(WIFI_USART, US_IER_RXRDY);
	
	/*Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

void configure_wifi_comm_pin(void){
	pmc_enable_periph_clk(WIFI_COMM_PIN_ID);
	pio_set_debounce_filter(WIFI_COMM_PIN_PIO, WIFI_COMM_PIN_MASK, 10);
	pio_handler_set(WIFI_COMM_PIN_PIO, WIFI_COMM_PIN_ID, WIFI_COMM_PIN_MASK,
			WIFI_COMM_PIN_ATTR, wifi_command_response_handler);
	NVIC_EnableIRQ((IRQn_Type)WIFI_COMM_PIN_ID);
	pio_enable_interrupt(WIFI_COMM_PIN_PIO, WIFI_COMM_PIN_MASK);
}
	
void process_incoming_byte_wifi(uint8_t in_byte){
	input_line_wifi[input_pos_wifi++] = in_byte; // I hate this syntax with a passion
}

void process_data_wifi(void){
	if(strstr(input_line_wifi, "Unknown command")){
		ioport_toggle_pin_level(LED_PIN);
	}
}