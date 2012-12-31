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


#include "../include/header.h"


/* Bars array dynamic creation and initialization */
bars *bar_create(int num_bars) {
	int i, space, border, size, tot_size, diff, tmp, y1, y2;
	char notes[7][2] = NOTES;
	char *sound_names[NUM_MAX_SOUNDS] = SOUND_FILES;
	bars *bar;
	
	/* Bars must be less than defined sounds */
	__ASSERT((num_bars <= NUM_MAX_SOUNDS), ERROR_NOT_ENOUGH_SOUNDS);
	
	/* Allocate bars array */
	bar = malloc(num_bars*sizeof(bars));
	__ASSERT(bar, ERROR_MEM_ALLOC);
	
	/* Calculate space, screen border and bar size in relation to resolution */
	space = __SPACE(num_bars);
	border = (int)(2.5*(float)space);
	size = (int)(7.5*(float)space);
	
	/* Now calculate unused space to distribute them */
	tot_size = border*2 + (num_bars*(size+space)) - space;
	diff = SCREEN_W - tot_size;
	
	if(diff > num_bars) { // if there are more unused pixels than bars: resize bars
		tmp = (int)((float)diff/(float)num_bars);
		size += tmp;
		diff -= tmp*num_bars;
	}
	if(diff > (num_bars-1)) { // if there are more unused pixels than spaces between bars: resize spaces
		tmp = (int)((float)diff/(float)(num_bars-1));
		space += tmp;
		diff -= tmp*(num_bars-1);
	}
	if(diff > 2) { // if there are more than 2 unused pixels: resize borders
		border += (int)((float)diff*0.5);
	}
	
	/* Calculate bars vertical position and height */
	y1 = BAR_TOP;
	y2 = BAR_BOTTOM;
	
	/* Initialize bars array with calculated datas */
	for(i=0;i<num_bars;i++) {
		bar[i].min.x = border + (size+space)*i;	// left
		bar[i].min.y = y1;				// top
		bar[i].max.x = bar[i].min.x + size;		// right
		bar[i].max.y = y2;				// bottom
		
		bar[i].t_start = -1;			// when bar color is "black", t_start is -1
		bar[i].color = 0;			// if (r,g,b) is (0,0,0) color is "black"
		bar[i].note[0] = notes[i%7][0];		// note corresponding to bar
		bar[i].note[1] = notes[i%7][1];		// this is '\0' term char
		
		// sample initialization and association to actual bar
		bar[i].sound = load_sample(sound_names[i]);
		__ASSERT(bar[i].sound, ERROR_CANT_LOAD_SAMPLE(sound_names[i]));
		
		// voice initialization and association to actual bar
		bar[i].voice = allocate_voice(bar[i].sound);
		__ASSERT(bar[i].voice != -1, ERROR_CANT_ALLOC_VOICE(i));
	}
	
	return bar;
}

/* This function is called if available hardware voices are less than bars, to deallocate all the voices and reallocate the first hw_voices voices. It also sets and returns an array called unused_voices of size hw_voices to contain the map (allocated voices, bar_number) */
int *reallocate_voices(bars *bar, int hw_voices) {
	int i;
	int *used_voices;
	
	for(i=0;i<NUM_BARS;i++) // deallocate all the already allocated voices
		deallocate_voice(bar[i].voice);
	
	used_voices = malloc(hw_voices*sizeof(int));
	__ASSERT(used_voices, ERROR_MEM_ALLOC);
	
	/* Voices re-initialization, allocating only the voices corresponding to the first hw_voices bars */
	for(i=0;i<hw_voices;i++) {
		bar[i].voice = allocate_voice(bar[i].sound);
		used_voices[i] = i;
	}
	
	return used_voices;
}
