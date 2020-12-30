/*
 * audio.c
 *
 * Created: 12/25/2020 1:38:42 AM
 *  Author: Benjamin Hicks
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "music.h"
#include "audio.h"

volatile uint8_t song_playing_flag = 0;
volatile const uint16_t *current_song = 0;
volatile uint16_t current_note_index = 0;

void audio_speaker_init()
{
	// make PORTC pin 7 high to prevent speaker power-down
	PORTC.OUTSET = PIN7_bm;
	PORTC.DIRSET = PIN7_bm;
	
	// make PORTA PIN3 (Analog Out) an output
	PORTA.DIRSET = PIN3_bm;
}

void audio_tcc1_init(void)
{
	// using tcc1 as the source for the DMA
	// means the OVF bit needs to be cleared.
	// to avoid additional interrupt overhead,
	// we use an event to reset the waveform
	
	// use event channel 1
	EVSYS.CH1MUX = EVSYS_CHMUX_TCC1_OVF_gc;
	TCC1.CTRLD = TC_EVACT_RESTART_gc | TC_EVSEL_CH1_gc;
	
	// reset count, default period of 0, and keep timer off
	TCC1.CNT = 0;
	TCC1.PER = 0;
	TCC1.CTRLA = TC_CLKSEL_OFF_gc;
}

void audio_tcd1_init(void)
{
	TCD1.CNT = 0;
	TCD1.PER = 0; // value determined by song
	TCD1.INTCTRLA = TC_OVFINTLVL_LO_gc;
	TCD1.CTRLA = TC_CLKSEL_OFF_gc;
}

void audio_play(const uint16_t* song)
{
	if (!song_playing_flag)
	{
		TCC1.CNT = 0;
		TCD1.CNT = 0;
		song_playing_flag = 1;
		current_note_index = 0;
		current_song = song;
		TCD1.PER = pgm_read_word(&current_song[current_note_index++]);
		
		// start playing the song
		TCD1.CTRLA = TC_CLKSEL_DIV1024_gc;
	}
}

void audio_stop(void)
{
	if (song_playing_flag)
	{
		TCD1.CTRLA = TC_CLKSEL_OFF_gc;
		TCC1.CTRLA = TC_CLKSEL_OFF_gc;
		song_playing_flag = 0;
		current_song = 0;
		current_note_index = 0;
	}
}

ISR(TCD1_OVF_vect)
{
	uint16_t note = pgm_read_word(&current_song[current_note_index]);
	
	// song has ended
	if (note == END)
	{
		TCD1.CTRLA = TC_CLKSEL_OFF_gc;
		TCC1.CTRLA = TC_CLKSEL_OFF_gc;
		song_playing_flag = 0;
		current_song = 0;
		current_note_index = 0;
	}
	else 
	{
		if (note == REST)
		{
			TCC1.CTRLA = TC_CLKSEL_OFF_gc;
		}
		else
		{
			TCC1.PER = note;
			TCC1.CTRLA = TC_CLKSEL_DIV1_gc;
		}
		current_note_index++;
	}
}