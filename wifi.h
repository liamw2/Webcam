/*
 * wifi.h
 *
 * Created: 2/9/2021 5:16:12 AM
 *  Author: zengl
 */ 


#ifndef WIFI_H_
#define WIFI_H_
#include <asf.h>
#include "camera.h"
 
#define BOARD_ID_USART             ID_USART0
#define WIFI_USART                 USART0
#define BOARD_USART_BAUDRATE       115200
#define USART_Handler              USART0_Handler
#define USART_IRQn                 USART0_IRQn

/** USART1 pin RX */ 
#define PIN_USART0_RXD    {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin TX */
#define PIN_USART0_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin CTS */
#define PIN_USART0_CTS    {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin RTS */
#define PIN_USART0_RTS    {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)  

#define WIFI_COMM_PIN_MASK			PIO_PA13
#define WIFI_COMM_PIN_PIO			PIOA
#define WIFI_COMM_PIN_ID			ID_PIOA
#define WIFI_COMM_PIN_TYPE			PIO_INPUT
#define WIFI_COMM_PIN_ATTR			PIO_IT_RISE_EDGE

#define ALL_INTERRUPT_MASK 0xffffffff

volatile uint32_t recieved_byte_wifi;
volatile uint8_t input_line_wifi[1000];
volatile uint32_t input_pos_wifi;


void wifi_usart_handler(void);
void process_incoming_byte_wifi(uint8_t in_byte);
void process_data_wifi(void);
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask);
void configure_usart_wifi(void);
void configure_wifi_comm_pin(void);
void write_wifi_command(char* comm, uint8_t cnt);
void write_image_to_file(void);

#endif /* WIFI_H_ */