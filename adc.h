/*
 * adc.h
 *
 * Created: 12/24/2020 4:10:38 PM
 *  Author: Benjamin Hicks
 */ 


#ifndef ADC_H_
#define ADC_H_

/***************************************
 * void adc_init(void) --
 *	This function initializes the ADC module
 *	we want to use to measure the voltage
 *	of our CdS cell. Based on the schematic,
 *	we should use the ADC on PORTA. We will
 *	use the differential with gain mode
 *	instead of the differential without gain
 *	mode because of the pin locations.
 *	
 *	To do our samples, we will trigger a conversion
 *	from an event channel (based on a timer) and 
 *	configure an interrupt to handle a completed read
 *
 *	We will produce 8-bit signed results and use a
 *	2.5V reference voltage (generated from OOTB board)
 *
 *	We will perform a conversion once per second
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: ADCA
 *
 **************************************/
void adc_init(void);


/***************************************
 * void adc_tcc0_init(void) --
 *	This function configures the event
 *	system such that event channel 0 is
 *	triggered by an overflow on TCC0.
 *	
 *	The timer is configured to overflow
 *	one time per second with the per_clk
 *	set to 32MHz
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCC0, EVSYS
 *
 **************************************/
void adc_tcc0_init(void);


#endif /* ADC_H_ */