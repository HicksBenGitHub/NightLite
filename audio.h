/*
 * audio.h
 *
 * Created: 12/25/2020 1:36:14 AM
 *  Author: Benjamin Hicks
 */ 


#ifndef AUDIO_H_
#define AUDIO_H_

#include "music.h"

/***************************************
 * void audio_speaker_init(void) --
 *	This function will enable the speaker
 *	on the OOTB Analog Backpack through
 *	PORTA and PORTC pins.
 *
 *	See Analog Backpack schematic for
 *	more information
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: PORTA, PORTC
 *
 **************************************/
void audio_speaker_init(void);

/***************************************
 * void audio_tcc1_init(void) --
 *	This function will configure TCC1,
 *	which will trigger DMA CH0 for the
 *	audio output.
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCC1, EVSYS
 *
 **************************************/
void audio_tcc1_init(void);

/***************************************
 * void audio_tcD1_init(void) --
 *	This function will configure TCD1,
 *	which will trigger control the TCC1
 *	timer
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCD1
 *
 **************************************/
void audio_tcd1_init(void);

/***************************************
 * void audio_play(const uint16_t* song) --
 *	This function will play the notes
 *	pointed to by song. song is terminated
 *  with 0xFFFF. Any "rest" notes are given
 *	with a period of 0. TCD1 controls the
 *	rate of play_back.
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCC1, TCD1, DMA, speaker
 *
 **************************************/
void audio_play(const uint16_t* song);

/***************************************
 * void audio_stop(void) --
 *	This function will stop the playback
 *	of notes.
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: TCC1, TCD1, DMA, speaker
 *
 **************************************/
void audio_stop(void);


#endif /* AUDIO_H_ */