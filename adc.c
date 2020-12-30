/*
 * adc.c
 *
 * Created: 12/24/2020 4:19:28 PM
 *  Author: Benjamin Hicks
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

volatile uint8_t adc_data_ready_flag = 0;
volatile int8_t adc_ch0_data = 0;

void adc_init(void)
{
	// select reference voltage
	ADCA.REFCTRL = ADC_REFSEL_AREFB_gc;
	
	// make ADCA slow to reduce power consumption
	ADCA.PRESCALER = ADC_PRESCALER_DIV512_gc;
	
	// generate 8-bit signed results
	ADCA.CTRLB = ADC_CONMODE_bm | ADC_RESOLUTION_8BIT_gc;
	
	// sample using CH0 of the ADCA module from event channel 0
	ADCA.EVCTRL = ADC_SWEEP_0_gc | ADC_EVSEL_0123_gc | ADC_EVACT_CH0_gc;
	
	// configure CH0 of the ADCA module as differential with gain
	ADCA.CH0.CTRL = ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;
	
	// ADCA CH0 positive input is PORTA pin 1, negative input is PORTA pin 6
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN1_gc | ADC_CH_MUXNEG_PIN6_gc;
	
	// ADCA CH0 will trigger an interrupt after a successful read completion
	ADCA.CH0.INTCTRL = ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_LO_gc;
	
	// enable the ADCA module after completing all initialization steps
	ADCA.CTRLA = ADC_ENABLE_bm;
}

ISR(ADCA_CH0_vect)
{
	adc_data_ready_flag = 1;
	adc_ch0_data = ADCA.CH0.RESL;
}

void adc_tcc0_init(void)
{
	// event channel 0 source will be TCC0
	EVSYS.CH0MUX = EVSYS_CHMUX_TCC0_OVF_gc;
	
	// 1 second overflow at 32MHz achieved with
	// a PER of 31250 and PRE of DIV1024
	TCC0.CNT = 0;
	TCC0.PER = 31250;
	TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
}