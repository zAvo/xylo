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

#ifndef _NO3BUF

extern volatile int timer;


void triple_buffer(BITMAP **page) {
	int i = 0, w, repeat, active_page = 0;
	int time_diff, bar_number, *used_voices = NULL, hw_voices;
	int text_bar_height, half_bar_size;
	unsigned int radius;
	
	coord_t dot[2], dot_old[2], cal[2], cal_tmp[2];
	
	wiimote *wiimote;
	
	char *fonts[NUM_MAX_FONTS] = FONTS;
	FONT *font_msg, *font_notes;
	BITMAP *background;
	bars *bar;
	
	/* dot_old data initialization. dot_old's X coord is not used */
	dot_old[0].y = SCREEN_H;
	dot_old[1].y = SCREEN_H;
	
	/* Wiimote initialization*/
	wiimote = *wiiuse_init(1);
	
	/* Load fonts, size of font is related to SCREEN_W */
	do {
		font_msg = load_font(fonts[i], NULL, NULL);
		__ASSERT(font_msg, ERROR_CANT_LOAD_FONT(fonts[i]));
		w = text_length(font_msg, WIIMOTE_CONNECTION_MSG);
	} while (w >= SCREEN_W && ++i < (NUM_MAX_FONTS-1));
	
	/* Notes' font is smaller than messages' font */
	font_notes = load_font(fonts[i], NULL, NULL);
	__ASSERT(font_notes, ERROR_CANT_LOAD_FONT(fonts[i]));
	
	/* Initialize and calculate bars size, point radius, text bar height, and calculate half bar size for text output under bars */
	bar = bar_create(NUM_BARS);
	radius = RADIUS(bar);
	text_bar_height = TEXT_BAR_HEIGHT;
	half_bar_size = HALF_BAR_SIZE(bar);
	
	/* Control the max number of available hardware voices. Though ALSA driver voices are up to 64, max hardware voices generally are 8-16. Checking the allocated voices after the driver allocation seems to be the only way */
	hw_voices = get_mixer_voices();
	if (hw_voices < NUM_BARS)
		used_voices = reallocate_voices(bar, hw_voices);
	
	/* Install timer, 10 ticks a second */
	LOCK_VARIABLE(timer);
	LOCK_FUNCTION(inc_timer);
	install_int_ex(inc_timer, BPS_TO_TIMER(10));
	
	/* Load background from file */
	background = load_tga("images/back.tga", NULL);
	__ASSERT(background, ERROR_CANT_LOAD_IMAGE("back.tga"));
	
	/* Enables vertical syncronization*/
	vsync();
	
	i = 0;
	/* First frame, this lasts until wiimote is connected, the user is prompted to activate the wiimote by pressing 1 & 2 keys on the wiimote */
	while(i == 0 && !keypressed()) {
		active_page = start_credits3buf(page, active_page);
		
		clear_keybuf();
		
		title3buf(page, active_page, font_msg);
		
		clear_keybuf();
		
		repeat = 0;
		while(repeat++ < 8 && i == 0 && !keypressed()) {
			stretch_blit(background, page[active_page], 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H); // background
			if(repeat%2 == 1)
				textout_centre_ex(page[active_page], font_msg, WIIMOTE_CONNECTION_MSG, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1); // text prompt
			
			release_bitmap(page[active_page]);
			/* make sure the last flip request has actually happened */
			do {
			} while (poll_scroll());
			
			/* post a request to display the page we just drew */
			request_video_bitmap(page[active_page]);

			/* update counters to point to the next page */
			switch (active_page) {
				case 0: active_page = 1; break;
				case 1: active_page = 2; break;
				case 2: active_page = 0; break;
			}

			/* Search for a wiimote */
			i = wiiuse_find(&wiimote, 1, 1);
		}
	}
	
	/* Try to connect to the wiimote */
	__ASSERT(wiiuse_connect(&wiimote, 1) > 0, ERROR_CANT_OPEN_WIIMOTE);
	
	/* Activate the first led on the wiimote */
	wiiuse_set_leds(wiimote, WIIMOTE_LED_1);
	
	/* Activate the ir module on the wiimote */
	wiiuse_set_ir(wiimote, TRUE);
	
	wiiuse_motion_sensing(wiimote, FALSE);
	
	wiiuse_set_ir_sensitivity(wiimote, 1);
	wiiuse_set_flags(wiimote, WIIUSE_CONTINUOUS, 0);
	
	cal[0].x = 0;
	cal[0].y = 0;
	cal[1].x = 1023;
	cal[1].y = 767;
	
	/* CALIBRATION LOOP */
	for(repeat=0;repeat<2;repeat++) {
		clear_keybuf();
		
		while(!keypressed()) {
			if (wiiuse_poll(&wiimote, 1)) // if there are datas pending from/to wiimote or ESC is pressed
				if (key[KEY_ESC] || wiimote->event == WIIUSE_DISCONNECT || wiimote->event == WIIUSE_UNEXPECTED_DISCONNECT || IS_PRESSED(wiimote, WIIMOTE_BUTTON_HOME)) { // if ESC is pressed, if wiimote update fails, or if HOME key on wiimote is pressed
				wiiuse_disconnect(wiimote);
				destroy_bitmap(background);
				destroy_font(font_msg);
				destroy_font(font_notes);
				for (i=0;i<NUM_BARS;i++) {
					deallocate_voice(bar[i].voice);
					destroy_sample(bar[i].sound);
				}
				free(bar); // YO!! :-)
				free(used_voices);
				
				return;
				}
			/* background */
			stretch_blit(background, page[active_page], 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);
			
			if (wiimote->ir.dot[0].visible) { // if ir source is visible
				/* Read coords from the wiimote's ir*/
				dot[0] = transpose(wiimote->ir.dot[0], cal, 0);
			}
			
			switch(repeat) {
				case 0:
					textout_centre_ex(page[active_page], font_msg, WIIMOTE_CAL_ASX, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1); // text prompt
					rect(page[active_page], dot[0].x, dot[0].y, SCREEN_W+1, SCREEN_H+1, makecol(0, 0, 0));
					break;
				case 1:
					textout_centre_ex(page[active_page], font_msg, WIIMOTE_CAL_BDX, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1); // text prompt
					
					rect(page[active_page], dot[1].x, dot[1].y, SCREEN_W+1, SCREEN_H+1, makecol(0, 0, 0));
					rect(page[active_page], -1, -1, dot[0].x, dot[0].y, makecol(0, 0, 0));
					break;
			}
			circlefill(page[active_page], dot[0].x, dot[0].y, radius, makecol(0, 0, 0));

			release_bitmap(page[active_page]);
			
			/* make sure the last flip request has actually happened */
			do {
			} while (poll_scroll());

			/* post a request to display the page we just drew */
			request_video_bitmap(page[active_page]);

			/* update counters to point to the next page */
			switch (active_page) {
				case 0: active_page = 1; break;
				case 1: active_page = 2; break;
				case 2: active_page = 0; break;
			}
		}
		
		cal_tmp[repeat].x = wiimote->ir.dot[0].x;
		cal_tmp[repeat].y = wiimote->ir.dot[0].y;
		dot[1] = dot[0];
	}
	
	__ASSERT((cal_tmp[0].x < cal_tmp[1].x && cal_tmp[0].y > cal_tmp[1].y), ERROR_WHILE_CALIBRATING);
	
	cal[0].x = cal_tmp[0].x;
	cal[0].y = 767-cal_tmp[0].y;
	cal[1].x = cal_tmp[1].x;
	cal[1].y = 767-cal_tmp[1].y;
	
	/* MAIN LOOP */
	while (TRUE) {
		/* Draw a frame */
		if (wiiuse_poll(&wiimote, 1) || key[KEY_ESC]) // if there are datas pending from/to wiimote or ESC is pressed
			if (key[KEY_ESC] || wiimote->event == WIIUSE_DISCONNECT || wiimote->event == WIIUSE_UNEXPECTED_DISCONNECT || IS_PRESSED(wiimote, WIIMOTE_BUTTON_HOME)) { // if ESC is pressed, if wiimote update fails, or if HOME key on wiimote is pressed
				wiiuse_disconnect(wiimote);
				destroy_bitmap(background);
				destroy_font(font_msg);
				destroy_font(font_notes);
				for (i=0;i<NUM_BARS;i++) {
					deallocate_voice(bar[i].voice);
					destroy_sample(bar[i].sound);
				}
				free(bar); // YO!! :-)
				free(used_voices);
				
				return;
			}
		
		/* background */
		stretch_blit(background, page[active_page], 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);
		
		/* Xylophone's bars and notes names */
		for(i=0;i<NUM_BARS;i++) {
			if (bar[i].t_start != -1 && (time_diff = timer-bar[i].t_start) > TICKS_TO_BLACK) // if color animation ends
				bar[i].t_start = -1;
			if (bar[i].t_start == -1) // if no color animation
				bar[i].color = 0;
			else	bar[i].color = COLORVAL(time_diff); // if color animation is running
			
			/* Draw bar */
			rectfill(page[active_page], bar[i].min.x, bar[i].min.y, bar[i].max.x, bar[i].max.y, makecol(bar[i].color, bar[i].color, bar[i].color));
			/* Print bar's associated note */
			textout_centre_ex(page[active_page], font_notes, bar[i].note, (bar[i].min.x + half_bar_size), text_bar_height, makecol(0, 0, 0), -1);
		}
		
		// da normalizzare e da contenere nello schermo, ir
		for(i=0;i<MAX_IR_DOTS;i++) {
			if (wiimote->ir.dot[i].visible) { // if ir source is visible
				/* Read coords from the wiimote's ir*/
				dot[i] = transpose(wiimote->ir.dot[i], cal, radius);
				
				/* If the ir source is under the bars and in previous frame it was above the bars, then play the sound and start the animation */
				if (dot[i].y > bar[0].min.y-radius) {
					if(dot_old[i].y <= bar[0].min.y-radius) {
						/* This calculates on which bar the ir source actually is */
						bar_number = is_onbar(bar, dot[i].x, NUM_BARS);
						
						/* play bar_number's sound with specified volume */
						play_bar_voice(bar, bar_number, volume(dot[i].y-dot_old[i].y), used_voices, hw_voices);
					}
					
					/* The dot have not to go under the bars or out of the screen */
					circlefill(page[active_page], dot[i].x, bar[0].min.y-radius, radius, makecol(0, 0, 0));
				}
				else	circlefill(page[active_page], dot[i].x, dot[i].y, radius, makecol(0, 0, 0));
				
				dot_old[i].y = dot[i].y;
			}
			else dot_old[i].y = SCREEN_H;
		}

		release_bitmap(page[active_page]);

		/* make sure the last flip request has actually happened */
		do {
		} while (poll_scroll());

		/* post a request to display the page we just drew */
		request_video_bitmap(page[active_page]);

		/* update counters to point to the next page */
		switch (active_page) {
			case 0: active_page = 1; break;
			case 1: active_page = 2; break;
			case 2: active_page = 0; break;
		}
	}
}
#endif /* _NO3BUF */
