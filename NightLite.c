/*
 * NightLite.c
 *
 * Created: 12/23/2020 12:48:15 PM
 * Author : Benjamin Hicks
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "rgb.h"
#include "dma.h"
#include "dac.h"
#include "audio.h"
#include "music.h"
#include "uart.h"

extern void clock_init(void);
extern uint8_t adc_data_ready_flag;
extern int8_t adc_ch0_data;
extern uint8_t uart_data_ready_flag;
extern uint8_t uart_data;

extern uint16_t *songs[SONGS_COUNT];
extern uint32_t *color_patterns[COLOR_PATTERNS_COUNT];

int main(void)
{
	// call initialization routines
	clock_init();
	adc_init();
	adc_tcc0_init();
	rgb_init();
	rgb_tcd0_init();
	dma_init();
	dac_init();
	audio_tcc1_init();
	audio_speaker_init();
	audio_tcd1_init();
	uart_init();
	
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	sei();
	
	// assume it is daytime to begin with
	uint8_t daytime = 1;
	
	// table needs to be updated to begin with
	uint8_t update_table = 1;
	
	// setup table in PuTTy
	enum SONGS night_song = BRAHMS_LULLABY;
	enum SONGS day_song = FUR_ELISE;
	enum COLOR_PATTERNS night_pattern = RAINBOW;
	enum COLOR_PATTERNS day_pattern = NO_COLOR;
	int8_t light_sensitivity = 0;
	
	uint8_t current_row = 0;
	
	while(1)
	{
		if (update_table)
		{
			update_table = 0;
			uart_out_char(0x0c);
			uart_out_string("SETTINGS\r\n--------\r\n");
			
			if (uart_data == 'a' || uart_data == 'A')
			{
				if (current_row == 0 && night_song)
					night_song--;
				else if (current_row == 1 && day_song)
					day_song--;
				else if (current_row == 2 && night_pattern)
					night_pattern--;
				else if (current_row == 3 && day_pattern)
					day_pattern--;
				else if (current_row == 4 && light_sensitivity > -128)
					light_sensitivity--;
			}
			else if (uart_data == 'd' || uart_data == 'D')
			{
				if (current_row == 0 && night_song < SONGS_COUNT - 1)
					night_song++;
				else if (current_row == 1 && day_song < SONGS_COUNT - 1)
					day_song++;
				else if (current_row == 2 && night_pattern < COLOR_PATTERNS_COUNT - 1)
					night_pattern++;
				else if (current_row == 3 && day_pattern < COLOR_PATTERNS_COUNT - 1)
					day_pattern++;
				else if (current_row == 4 && light_sensitivity < 127)
					light_sensitivity++;
			}
			else if ((uart_data == 'w' || uart_data == 'W') && current_row)
			{
				current_row--;
			}
			else if ((uart_data == 's' || uart_data == 'S') && current_row < 4)
			{
				current_row++;
			}
			
			uart_out_string("NIGHT SONG: ");
			switch(night_song)
			{
				case OFF:
					uart_out_string("<OFF>\r\n");
					break;
				case BRAHMS_LULLABY:
					uart_out_string("<Brahm's Lullaby>\r\n");
					break;
				case FUR_ELISE:
					uart_out_string("<Fur Elise>\r\n");
					break;
				case PACHELBEL_CANON:
					uart_out_string("<Pachelbel Canon>\r\n");
					break;
				default:
					uart_out_string("<ERROR!!!>\r\n");
			}
			
			uart_out_string("DAY SONG: ");
			switch(day_song)
			{
				case OFF:
				uart_out_string("<OFF>\r\n");
				break;
				case BRAHMS_LULLABY:
				uart_out_string("<Brahm's Lullaby>\r\n");
				break;
				case FUR_ELISE:
				uart_out_string("<Fur Elise>\r\n");
				break;
				case PACHELBEL_CANON:
				uart_out_string("<Pachelbel Canon>\r\n");
				break;
				default:
				uart_out_string("<ERROR!!!>\r\n");
			}
			
			uart_out_string("NIGHT COLOR PATTERN: ");
			switch(night_pattern)
			{
				case NO_COLOR:
				uart_out_string("<NO COLOR>\r\n");
				break;
				case RAINBOW:
				uart_out_string("<Rainbow>\r\n");
				break;
				case OCEAN_BLUE:
				uart_out_string("<Ocean Blue>\r\n");
				break;
				case FLAMING_RED:
				uart_out_string("<Flaming Red>\r\n");
				break;
				default:
				uart_out_string("<ERROR!!!>\r\n");
			}
			
			uart_out_string("DAY COLOR PATTERN: ");
			switch(day_pattern)
			{
				case NO_COLOR:
				uart_out_string("<NO COLOR>\r\n");
				break;
				case RAINBOW:
				uart_out_string("<Rainbow>\r\n");
				break;
				case OCEAN_BLUE:
				uart_out_string("<Ocean Blue>\r\n");
				break;
				case FLAMING_RED:
				uart_out_string("<Flaming Red>\r\n");
				break;
				default:
				uart_out_string("<ERROR!!!>\r\n");
			}
			
			uart_out_string("Light Sensitivity: ");
			uart_out_char('<');
			uart_out_int8_t(light_sensitivity);
			uart_out_string(">\r\n");
			
		}
		
		if (uart_data_ready_flag)
		{
			update_table = 1;
			uart_data_ready_flag = 0;
		}
		
		if (adc_data_ready_flag)
		{
			adc_data_ready_flag = 0;
			if (adc_ch0_data < light_sensitivity && daytime)
			{
				daytime = 0;
				audio_stop();
				audio_play(songs[night_song]);
				rgb_stop();
				rgb_play(color_patterns[night_pattern]);
			}
			else if (adc_ch0_data >= light_sensitivity && !daytime)
			{
				daytime = 1;
				audio_stop();
				audio_play(songs[day_song]);
				rgb_stop();
				rgb_play(color_patterns[day_pattern]);
			}
		}
	}
}
