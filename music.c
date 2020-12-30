/*
 * music.c
 *
 * Created: 12/25/2020 5:50:34 PM
 *  Author: Benjamin Hicks
 *
 *	This file contains the songs available to choose
 *	as tunes
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "music.h"


const uint16_t off[] PROGMEM = {
	1000,
	END
};

const uint16_t brahms_lullaby[] PROGMEM = {
	// tempo
	5000,
	
	// organized into 1 measure per row
	// BRAHMS_LULLABY is 3/4, we will break that into 12 notes / measure
	
	REST,REST,REST,REST,REST,REST,REST,REST, E4,REST, E4,REST,
	G4,G4,G4,G4,G4,G4,G4,REST, E4,REST, E4,REST,
	G4,G4,G4,G4,G4,G4,G4,REST, E4,REST, G4,REST,
	C5,C5,C5,REST, B4,B4,B4,REST, A4,A4,A4,REST,
	A4,A4,A4,REST, G4,G4,G4,REST, D4,REST, E4,REST,
	F4,F4,F4,REST, D4,D4,D4,REST, D4,REST, E4,REST,
	F4,F4,F4,F4,F4,F4,F4,REST, D4,REST, F4,REST,
	B4,REST, A4,REST, G4,G4,G4,REST, B4,B4,B4,REST,
	C5,C5,C5,C5,C5,C5,C5,REST, C4,REST, C4,REST,
	C5,C5,C5,C5,C5,C5,C5,REST, A4,REST, F4,REST,
	G4,G4,G4,G4,G4,G4,G4,REST, E4,REST, C4,REST,
	F4,F4,F4,REST, G4,G4,G4,REST, A4,A4,A4,REST,
	G4,G4,G4,G4,G4,G4,G4,REST, C4,REST, C4,REST,
	C5,C5,C5,C5,C5,C5,C5,REST, A4,REST, F4,REST,
	G4,G4,G4,G4,G4,G4,G4,REST, E4,REST, C4,REST,
	F4,F4,F4,REST, E4,E4,E4,REST, D4,D4,D4,REST,
	C4,C4,C4,C4,C4,C4,C4,REST, REST,REST,REST,REST,
	
	END
};

const uint16_t fur_elise[] PROGMEM = {
	// tempo
	3500,
	
	// organized into 1 measure per row
	// FUR_ELISE is 3/4, we will break that into 12 notes / measure
	E6,E6, D6_s,D6_s,
	
	E6,E6, D6_s,D6_s, E6,E6, B5,B5, D6,D6, C6,C6,
	A5,A5, E4,E4, A4,A4, C5,C5, E5,E5, A5,A5,
	B5,B5, G4_s,G4_s, B4,B4, E5,E5, G5_s,G5_s, B5,B5,
	C6,C6, E4,E4, A4,A4, E5,E5, E6,E6, D6_s,D6_s,
	E6,E6, D6_s,D6_s, E6,E6, B5,B5, D6,D6, C6,C6,
	A5,A5, E4,E4, A4,A4, C5,C5, E5,E5, A5,A5,
	B5,B5, G4_s,G4_s, B4,B4, E5,E5, C6,C6, B5,B5,
	// ________
	// |1.
	A5,A5, E4,E4, A4,A4, REST,REST, E6,E6, D6_s,D6_s,
	
	E6,E6, D6_s,D6_s, E6,E6, B5,B5, D6,D6, C6,C6,
	A5,A5, E4,E4, A4,A4, C5,C5, E5,E5, A5,A5,
	B5,B5, G4_s,G4_s, B4,B4, E5,E5, G5_s,G5_s, B5,B5,
	C6,C6, E4,E4, A4,A4, E5,E5, E6,E6, D6_s,D6_s,
	E6,E6, D6_s,D6_s, E6,E6, B5,B5, D6,D6, C6,C6,
	A5,A5, E4,E4, A4,A4, C5,C5, E5,E5, A5,A5,
	B5,B5, G4_s,G4_s, B4,B4, E5,E5, C6,C6, B5,B5,
	
	// ________
	// |2.
	A5,A5, E4,E4, A4,A4, B5,B5, C6,C6, D6,D6,
	E6,E6, G4,G4, C5,C5, G5,G5, F6,F6, E6,E6,
	D6,D6, G4,G4, B4,B4, F5,F5, E6,E6, D6,D6,
	C6,C6, E4,E4, A4,A4, E5,E5, D6,D6, C6,C6,
	B5,B5, E4,E4, E5,REST, E5,E5, E6,E6, E5,E5,
	E6,REST, E6,E6, E7,E7, D6_s,D6_s, E6,E6, D6_s,D6_s,
	E6,E6, D6_s,D6_s, E6,E6, D6_s,D6_s, E6,E6, D6_s,D6_s,
	
	END
};

const uint16_t pachelbel_canon[] PROGMEM = {
	// tempo
	5000,
	
	// PACHELBEL_CANON is 4/4, we will break that into 16 notes / measure
	C5,C5, E6,E6, G6,G6, C7,C7, G4,G4, D6,D6, G6,G6, B6,B6,
	A4,A4, C6,C6, E6,E6, A6,A6, E4,E4, B5,B5, E6,E6, G6,G6,
	F4,F4, A5,A5, C6,C6, F6,F6, C4,C4, G5,G5, C6,C6, E6,E6,
	F4,F4, A5,A5, C6,C6, F6,F6, G4,G4, B5,B5, D6,D6, G6,G6,
	
	E7,REST, G6,REST, C7,REST, G6,REST, D7,REST, G6,REST, B6,REST, G6,REST,
	C7,REST, E6,REST, A6,REST, E6,REST, B6,REST, E6,REST, G6,REST, E6,REST,
	A6,REST, C6,REST, F6,REST, C6,REST, G6,REST, C6,REST, E6,REST, C6,REST,
	A6,REST, C6,REST, F6,REST, C6,REST, B6,REST, D6,REST, G6,REST, D6,REST,
	
	C7,C7, B6,B6, C7,C7, B6, C7, B6,B6,B6,B6,B6,B6,B6,REST,
	C7,C7,C7,C7, E7,E7,E7,E7, G7,G7,G7,G7,G7,G7, A7,A7,
	F7,F7, E7,E7, D7,D7, F7,F7, E7,E7, D7,D7, C7,C7, B6,B6,
	A6,A6, G6,G6, F6,F6, E6,E6, D6,D6, F6,F6, E6,E6, D6,D6,
	
	C6,C6, D6,D6, E6,E6, F6,F6, G6,G6,G6,REST, G6,G6, F6,F6,
	E6,E6, A6,A6, G6,G6, F6,F6,	G6,G6, F6,F6, E6,E6, D6,D6, 
	C6,C6,C6,C6, A6,A6, B6,B6, C7,C7, B6,B6, A6,A6, G6,G6,
	A6,A6,A6,A6, B6,B6, C7,C7, B6, G6, A6, B6, C7, D7, E7, F7,
	
	G7,G7, E7, F7, G7,G7, E7, F7, G7, G6, A6, B6, C7, D7, E7, F7,
	E7,E7, C7, D7, E7,E7, E6, F6, G6, A6, G6, F6, G6, C7, B6, C7,
	A6,A6, C7, B6, A6,A6, G6, F6, G6, F6, E6, F6, G6, A6, B6, C7,
	A6,A6, C7, B6, C7,REST, C7,C7, B6, G6, A6, B6, C7, D7, E7, F7,
	
	G7,G7, E7, F7, G7,REST, G7,REST, G7,G7,G7,G7, F7,F7,F7,F7,
	E7,E7, C7, D7, E7,REST, E7,REST, E7,E7,E7,E7, D7,D7,D7,D7,
	C7,REST, C7, B6, A6,A6, G6, F6, G6, F6, E6, F6, G6, A6, B6, C7,
	A6,A6, C7, B6, C7,REST, C7,C7, B6,B6,B6,B6, G6,G6,G6,G6,
		
	END
};

const uint16_t *songs[SONGS_COUNT] = { off, brahms_lullaby, fur_elise, pachelbel_canon };