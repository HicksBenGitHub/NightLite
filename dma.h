/*
 * dma.h
 *
 * Created: 12/25/2020 12:27:14 AM
 *  Author: Benjamin Hicks
 */ 


#ifndef DMA_H_
#define DMA_H_

/***************************************
 * void dma_init(void) --
 *	This function will reset the DMA 
 *	system and initialize the DMA to
 *	handle the audio
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: DMA
 *
 **************************************/
void dma_init(void);

/***************************************
 * void dma_audio_init(void) --
 *	This function will setup channel 0
 *	to transfer the audio data
 *
 *	Input(s): None
 *	Output(s): None
 *	Affected: DMA
 *
 **************************************/
void dma_audio_init(void);

#endif /* DMA_H_ */