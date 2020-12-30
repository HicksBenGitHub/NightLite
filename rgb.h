/*
 * rgb.h
 *
 * Created: 12/25/2020 12:18:20 AM
 *  Author: Benjamin Hicks
 */ 


#ifndef RGB_H_
#define RGB_H_

#define RED_bp 4
#define RED_bm (1 << RED_bp)
#define GREEN_bp 5
#define GREEN_bm (1 << GREEN_bp)
#define BLUE_bp 6
#define BLUE_bm (1 << BLUE_bp)

/***************************************
 * void rgb_init(void) --
 *	This function will configure the PORTD
 *	pins of the ATxmega128A1U, which
 *	control the RGB LEDs on the OOTB uPAD
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: PORTD
 **************************************/
void rgb_init(void);

/***************************************
 * void rgb_tcd0_init(void) --
 *	This function will initialize the
 *	TCD0 timer, which will have CC regs
 *	we use to do PWM
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCD0
 **************************************/
void rgb_tcd0_init(void);

/***************************************
 * void rgb_play(uint32_t* colors) --
 *	This function will start the color
 *	pattern sequence, which uses the TCD0
 *	timer OVF interrupt to update the CC
 *	values to change colors
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCD0
 **************************************/
void rgb_play(uint32_t* colors);

/***************************************
 * void rgb_stop(void) --
 *	This function will stop the color
 *	pattern sequence
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCD0
 **************************************/
void rgb_stop(void);

enum COLOR_PATTERNS { NO_COLOR, RAINBOW, OCEAN_BLUE, FLAMING_RED, COLOR_PATTERNS_COUNT };

#endif /* RGB_H_ */