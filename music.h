/*
 * music.h
 *
 * Created: 12/25/2020 6:20:34 PM
 *  Author: Benjamin Hicks
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_

enum SONGS { OFF, BRAHMS_LULLABY, FUR_ELISE, PACHELBEL_CANON, SONGS_COUNT };
	
#define REST 0
#define END 0xFFFF

// MUSICAL NOTES - tuned using DAD to measure freq output
#define C4 485
#define C4_s 457
#define D4_b C4_s
#define D4 432
#define D4_s 407
#define E4_b D4_s
#define E4 384
#define F4 362
#define F4_s 342
#define G4_b F4_s
#define G4 322
#define G4_s 304
#define A4 287
#define A4_s 271
#define B4_b A4_s
#define B4 256
#define C5 241
#define C5_s 227
#define D5_b C5_s
#define D5 214
#define D5_s 202
#define E5_b D5_s
#define E5 190
#define F5 180
#define F5_s 169
#define G5_b F5_s
#define G5 160
#define G5_s 151
#define A5_b G5_s
#define A5 142
#define A5_s 134
#define B5_b A5_s
#define B5 126
#define C6 119
#define C6_s 112
#define D6_b C6_s
#define D6 106
#define D6_s 100
#define E6_b D6_s
#define E6 94
#define F6 88
#define F6_s 83
#define G6_b F6_s
#define G6 78
#define G6_s 74
#define A6_b G6_s
#define A6 70
#define A6_s 65
#define B6_b A6_s
#define B6 62
#define C7 58
#define C7_s 54
#define D7_b C7_s
#define D7 51
#define D7_s 48
#define E7_b D7_s
#define E7 45
#define F7 43
#define F7_s 40
#define G7_b F7_s
#define G7 38
#define G7_s 35
#define A7_b G7_s
#define A7 33
#define A7_s 31
#define B7_b A7_s
#define B7 29
#define C8 28


#endif /* MUSIC_H_ */