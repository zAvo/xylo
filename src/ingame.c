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

extern volatile int timer;


/* This function returns the volume value using the pixel difference between actual and previous y coord */
int volume(int diff) {
	return diff >= 64 ? 255 : diff*4;
}

/* This function returns screen coords from wiimote coords using the calibration datas acquired */
coord_t transpose(ir_dot_t dot, coord_t *cal, unsigned int radius) {
	coord_t res;

	if(dot.x < cal[0].x)
		res.x = 0;
	else if(dot.x > cal[1].x)
		res.x = SCREEN_W;
	else	res.x = (unsigned int)(((float)(dot.x - cal[0].x)*SCREEN_W)/(cal[1].x - cal[0].x));
	
	if(res.x < radius)
		res.x = radius;
	else if(res.x > SCREEN_W-radius)
		res.x = SCREEN_W-radius;
	
	if(dot.y < cal[0].y)
		res.y = 0;
	else if(dot.y > cal[1].y)
		res.y = SCREEN_H;
	else	res.y = (unsigned int)(((float)(dot.y - cal[0].y)*SCREEN_H)/(cal[1].y - cal[0].y));
	
	res.y = SCREEN_H - res.y;
	
	if(res.y < radius)
		res.y = radius;
	
	return res;
}

/* Plays the sound: if the sound is already allocated to a voice restarts the sound and sets the start time, else reallocate a voice that is not playing a sound or the former voice started if all hardware available voices are already playing. This is necessary because it seems that if we try to directly allocate a new voice, the voice "deallocated" is not the former but a random one, so we need to search for the older voice playing */
void play_bar_voice(bars *bar, int bar_to_play, int volume, int *used_voices, int hw_voices) {
	int i, t = timer, older = -1;
	
	// if the sample is already allocated to a voice restarts the voice with the new volume and sets the start time
	if (voice_check(bar[bar_to_play].voice) == bar[bar_to_play].sound) {
		voice_set_position(bar[bar_to_play].voice, 0);
		voice_set_volume(bar[bar_to_play].voice, volume);
		bar[bar_to_play].t_start = timer;
		voice_start(bar[bar_to_play].voice);
		
		return;
	}
	
	// search the older playing voice or a voice not playing
	for (i=0;i<hw_voices&&t>-1;i++) {
		if (t > bar[used_voices[i]].t_start) {
			t = bar[i].t_start;
			older = i;
		}
	}
	
	// update the (voice, bar) association
	used_voices[older] = bar_to_play;
	
	// reallocate the older bar voice with the new sample to play
	reallocate_voice(bar[older].voice, bar[bar_to_play].sound);
	__ASSERT(bar[older].voice != -1, ERROR_MEM_ALLOC);
	
	// associate the new voice to the bar to play
	bar[bar_to_play].voice = bar[older].voice;
	
	/* Play the newly allocated voice with the new volume and sets the start time */
	voice_set_volume(bar[bar_to_play].voice, volume);
	bar[bar_to_play].t_start = timer;
	voice_start(bar[bar_to_play].voice);
}

/* Bar under x coord */
int is_onbar(bars *bar, unsigned int x, int num_bars) {
	int i, half_space;
	
	// half space is used to "extend" the bars: there is no dead zone between two bars
	half_space = (bar[1].min.x - bar[0].max.x)/2;
	
	for(i=0;i<num_bars;i++)
		if(x < bar[i].max.x + half_space)
			return i;
	
	return (num_bars-1);
}
