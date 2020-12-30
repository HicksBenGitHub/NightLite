/*
 * dac.h
 *
 * Created: 12/25/2020 1:02:49 AM
 *  Author: Benjamin Hicks
 */ 

#ifndef DAC_H_
#define DAC_H_

/***************************************
 * void dac_init(void) --
 *	This function will configure the DAC
 *	to convert 16-bit unsigned data and
 *	output the voltage to the speaker on
 *	the OOTB Analog Backpack
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: DAC
 *
 **************************************/
void dac_init(void);

#endif /* DAC_H_ */