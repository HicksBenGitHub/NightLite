/*
 * dma.c
 *
 * Created: 12/25/2020 12:30:23 AM
 *  Author: Benjamin Hicks
 */ 

#include <avr/io.h>
#include "dma.h"

extern uint16_t LUT_SINE[256];
extern uint16_t rainbow[768];

void dma_init(void)
{
	// reset the DMA system
	DMA.CTRL = DMA_RESET_bm;
	
	// use CH0 to generate the audio, CH1 to generate the colors
	// give the audio a higher priority
	DMA.CTRL = DMA_DBUFMODE_DISABLED_gc | DMA_PRIMODE_CH0RR123_gc;
	
	dma_audio_init();
	
	// enable DMA
	DMA.CTRL |= DMA_ENABLE_bm;	
}

void dma_audio_init(void)
{
	// transfer 2 bytes per burst and use single-shot trigger mode
	// we will use repeat-mode so that we do not have to re-enable the channel
	// over and over again (we make repeat count 0 for infinite transaction)
	DMA.CH0.CTRLA =	DMA_CH_SINGLE_bm | DMA_CH_BURSTLEN_2BYTE_gc | DMA_CH_REPEAT_bm;
	DMA.CH0.REPCNT = 0;
	
	// configure the src and dest address controls
	// we want the src to be incrementing through our look-up table
	// reset the src after we reach end of LUT (1 block)
	// we want the destination to be fixed
	DMA.CH0.ADDRCTRL = DMA_CH_SRCRELOAD_BLOCK_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_INC_gc;
	
	// configure the transfer trigger to be based on TCC1 overflow
	DMA.CH0.TRIGSRC = DMA_CH_TRIGSRC_TCC1_OVF_gc;
	
	// we will use a look-up table
	DMA.CH0.TRFCNT = sizeof(LUT_SINE);
	
	// set the source and destination addresses
	DMA.CH0.SRCADDR0 = (uint8_t)((uintptr_t)LUT_SINE >> 0);
	DMA.CH0.SRCADDR1 = (uint8_t)((uintptr_t)LUT_SINE >> 8);
	DMA.CH0.SRCADDR2 = (uint8_t)((uint32_t)(uintptr_t)LUT_SINE >> 16);
	
	DMA.CH0.DESTADDR0 = (uint8_t)((uintptr_t)&DACA.CH1DATA >> 0);
	DMA.CH0.DESTADDR1 = (uint8_t)((uintptr_t)&DACA.CH1DATA >> 8);
	DMA.CH0.DESTADDR2 = (uint8_t)((uint32_t)(uintptr_t)&DACA.CH1DATA >> 16);
	
	// enable CH0
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
}