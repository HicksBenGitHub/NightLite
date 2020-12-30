/*
 * uart.h
 *
 * Created: 12/29/2020 7:53:23 PM
 *  Author: Benjamin Hicks
 */ 


#ifndef UART_H_
#define UART_H_

/***************************************
 * void uart_init(void) --
 *	This function initializes the UART
 *	system in PORTD to have a protocol of:
 *	1 start bit, 8 data bits, even parity,
 *	and 1 stop bit with a baud-rate of 2Mbps
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: PORTD, USARTD0
 *
 **************************************/
#define BSEL 0
#define BSCALE 0

#define PORTD_RX_bp 2
#define PORTD_RX_bm (1 << PORTD_RX_bp)
#define PORTD_TX_bp 3
#define PORTD_TX_bm (1 << PORTD_TX_bp)

void uart_init(void);

/***************************************
 * void uart_out_progmemc_string(const uint8_t* input_string) --
 *	This function transmits the characters pointed to by
 *	input_string (up to the null character) using polling
 *
 *	Input(s): uint8_t* input_string
 *	Output(s): None
 *	Affected: PORTD, USARTD0
 *
 **************************************/
void uart_out_string(const char* input_string);

/***************************************
 * void uart_out_char(uint8_t c) --
 *	This function outputs a single character
 *	via USARTD0
 *
 *	Input(s): uint8_t c
 *	Output(s): None
 *	Affected: PORTD, USARTD0
 *
 **************************************/
void uart_out_char(uint8_t c);

/***************************************
 * void uart_out_char(uint8_t c) --
 *	This function outputs a signed 8-bit integer
 *	via USARTD0
 *
 *	Input(s): uint8_t c
 *	Output(s): None
 *	Affected: PORTD, USARTD0
 *
 **************************************/
void uart_out_int8_t(int8_t val);

#endif /* UART_H_ */