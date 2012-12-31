/*
 *	Xylo
 *	Copyright 2008, 2009 Marco Mandrioli, Alberto Vespignani
 *
 *	This file is part of Xylo.
 *
 *	Xylo is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Xylo is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Xylo.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef _HEADER_XYLO
#define _HEADER_XYLO


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <allegro.h>
#include <winalleg.h>

#include "os_specific.h"
#include "constants.h"
#include "macros.h"


/* Types definitions*/

typedef struct {
	unsigned int x, y;
} coord_t;

typedef struct {
	coord_t min, max;
	
	int t_start;
	int color;
	
	char note[2];
	SAMPLE *sound;
	int voice;
} bars;

/* Timer function prototype */
void inc_timer(void);

/* Functions prototypes */
int volume(int diff);
int *reallocate_voices(bars *bar, int hw_voices);
void play_bar_voice(bars *bar, int bar_to_play, int volume, int *used_voices, int hw_voices);
int is_onbar(bars *bar, unsigned int x, int num_bars);
bars *bar_create(int num_bars);
void single_buffer();
void triple_buffer(BITMAP **page);
coord_t transpose(ir_dot_t dot, coord_t *cal, unsigned int radius);

#ifdef _NO3BUF
void start_credits(BITMAP *page);
void title(BITMAP *page, FONT *font_msg);
#else
int title3buf(BITMAP **page, int active_page, FONT *font_msg);
int start_credits3buf(BITMAP **page, int active_page);
#endif /* _NO3BUF */

#endif /* _HEADER_XYLO */
