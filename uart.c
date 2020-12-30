/*
 * uart.c
 *
 * Created: 12/29/2020 7:56:40 PM
 *  Author: Benjamin Hicks
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

volatile uint8_t uart_data_ready_flag = 0;
volatile uint8_t uart_data = 0;

void uart_init(void)
{
	// setup receiving characters to be via interrupt
	// character transmission will be handled using polling
	USARTD0.CTRLA = USART_RXCINTLVL_LO_gc;
	
	// enable RX and TX
	USARTD0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	// make RX and TX bits on PORTD outputs
	PORTD.DIRCLR = PORTD_RX_bm;
	PORTD.DIRSET = PORTD_TX_bm;
	
	// configure transmission mode
	USARTD0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_EVEN_gc | USART_CHSIZE_8BIT_gc;
	
	// configure BSEL and BSCALE
	USARTD0.BAUDCTRLA = (uint8_t)BSEL;
	USARTD0.BAUDCTRLB = (uint8_t)((BSCALE << 4) & 0xF0) | (uint8_t)((BSEL >> 8) & 0x0F);
}

void uart_out_string(const char* input_string)
{
	while(*input_string)
	{
		while(!(USARTD0.STATUS & USART_DREIF_bm));
		char data = *input_string++;
		USARTD0.DATA = data;
	}
}

void uart_out_char(uint8_t c)
{
	while(!(USARTD0.STATUS & USART_DREIF_bm));
	USARTD0.DATA = c;
}

ISR(USARTD0_RXC_vect)
{
	uart_data = USARTD0.DATA;
	uart_data_ready_flag = 1;
}

void uart_out_int8_t(int8_t val)
{
	if (val == -128) uart_out_string("-128");
	else
	{
		if (val < 0)
		{
			uart_out_char('-');
			val *= -1;
		}
		
		uint8_t digit0 = '0' + (val % 10);
		val /= 10;
		uint8_t digit1 = '0' + (val % 10);
		val /= 10;
		uint8_t digit2 = '0' + (val % 10);
		
		if (digit2 != '0')
		{
			uart_out_char(digit2);
			uart_out_char(digit1);
			uart_out_char(digit0);
		}
		else if (digit1 != '0')
		{
			uart_out_char(digit1);
			uart_out_char(digit0);
		}
		else
		{
			uart_out_char(digit0);
		}
	}
}