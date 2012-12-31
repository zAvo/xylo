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

int start_credits3buf(BITMAP **page, int active_page) {
	int i, alpha = 0, t_start = timer, space_w, space_h;
	
	BITMAP *sprite[3];
	
	sprite[0] = load_tga("images/wiiuse.tga", NULL);
	__ASSERT(sprite[0], ERROR_CANT_LOAD_IMAGE("wiiuse.tga"));
	sprite[1] = load_tga("images/allegro.tga", NULL);
	__ASSERT(sprite[1], ERROR_CANT_LOAD_IMAGE("wiiuse.tga"));
	sprite[2] = load_tga("images/gplv3.tga", NULL);
	__ASSERT(sprite[2], ERROR_CANT_LOAD_IMAGE("wiiuse.tga"));
	
	space_w = (int)((float)(SCREEN_W - sprite[0]->w - sprite[1]->w)/3);
	space_h = (int)((float)(SCREEN_H - sprite[0]->h - sprite[2]->h)/3);
	
	while (alpha < 256 && !keypressed()) {
		acquire_bitmap(page[active_page]);
		clear_bitmap(page[active_page]);

		clear_to_color(page[active_page], makecol(0, 0, 0));
		
		set_trans_blender(0, 0, 0, alpha);
		if (space_w >= 0) {
			draw_trans_sprite(page[active_page], sprite[0], space_w, space_h);
			draw_trans_sprite(page[active_page], sprite[1], space_w*2+sprite[0]->w, space_h);
			draw_trans_sprite(page[active_page], sprite[2], (int)(((float)(SCREEN_W-sprite[2]->w))/2), space_h*2+sprite[0]->h);
		}
		else	draw_trans_sprite(page[active_page], sprite[0], (int)(((float)(SCREEN_W-sprite[0]->w))/2), (int)(((float)(SCREEN_H-sprite[0]->h))/2));
		
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
		
		alpha = (int)(((float)(timer-t_start))*10);
	}
	
	if (keypressed()) {
		destroy_bitmap(sprite[0]);
		destroy_bitmap(sprite[1]);
		destroy_bitmap(sprite[2]);
		
		return active_page;
	}
	
	if (space_w < 0) {
		for (i=0;i<2;i++) {
			t_start = timer;
			alpha = 0;
			
			while (alpha < 256 && !keypressed()) {
				acquire_bitmap(page[active_page]);
				clear_bitmap(page[active_page]);
				
				clear_to_color(page[active_page], makecol(0, 0, 0));
				
				set_trans_blender(0, 0, 0, 255 - alpha);
				draw_trans_sprite(page[active_page], sprite[i], (int)(((float)(SCREEN_W-sprite[i]->w))/2), (int)(((float)(SCREEN_H-sprite[i]->h))/2));
				
				set_trans_blender(0, 0, 0, alpha);
				draw_trans_sprite(page[active_page], sprite[i+1], (int)(((float)(SCREEN_W-sprite[i+1]->w))/2), (int)(((float)(SCREEN_H-sprite[i+1]->h))/2));
				
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
				
				alpha = (int)(((float)(timer-t_start))*10);
			}
		}
	}
	
	
	if (keypressed()) {
		destroy_bitmap(sprite[0]);
		destroy_bitmap(sprite[1]);
		destroy_bitmap(sprite[2]);
		
		return active_page;
	}
	
	if (space_w >= 0)
		for(i=0;i<4;i++) {
			if(keypressed()) {
				destroy_bitmap(sprite[0]);
				destroy_bitmap(sprite[1]);
				destroy_bitmap(sprite[2]);
				
				return active_page;
			}
			
			rest(500);
		}
	
	t_start = timer;
	alpha = 0;
	
	while (alpha < 256 && !keypressed()) {
		acquire_bitmap(page[active_page]);
		clear_bitmap(page[active_page]);

		clear_to_color(page[active_page], makecol(0, 0, 0));
		
		set_trans_blender(0, 0, 0, 255-alpha);
		if (space_w >= 0) {
			draw_trans_sprite(page[active_page], sprite[0], space_w, space_h);
			draw_trans_sprite(page[active_page], sprite[1], space_w*2+sprite[0]->w, space_h);
			draw_trans_sprite(page[active_page], sprite[2], (int)(((float)(SCREEN_W-sprite[2]->w))/2), space_h*2+sprite[0]->h);
		}
		else	draw_trans_sprite(page[active_page], sprite[2], (int)(((float)(SCREEN_W-sprite[2]->w))/2), (int)(((float)(SCREEN_H-sprite[2]->h))/2));
		
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
		
		alpha = (int)(((float)(timer-t_start))*10);
	}
	
	destroy_bitmap(sprite[0]);
	destroy_bitmap(sprite[1]);
	destroy_bitmap(sprite[2]);

	return active_page;
}

int title3buf(BITMAP **page, int active_page, FONT *font_msg) {
	int i = 0, r, g, b, alpha = 0, t_tick = timer, t_start = timer, space_w, space_h;
	
	BITMAP *sprite;
	
	if(SCREEN_W >= 1280) {
		sprite = load_tga("images/Xylo1280.tga", NULL);
		__ASSERT(sprite, ERROR_CANT_LOAD_IMAGE("Xylo1280.tga"));
	}
	else {
		sprite = load_tga("images/Xylo640.tga", NULL);
		__ASSERT(sprite, ERROR_CANT_LOAD_IMAGE("Xylo640.tga"));
	}
	
	space_w = (int)((float)(SCREEN_W - sprite->w)/2);
	space_h = (int)((float)(SCREEN_H - sprite->h)/2);
	
	clear_keybuf();
	
	while (alpha < 256 && !keypressed()) {
		acquire_bitmap(page[active_page]);
		clear_bitmap(page[active_page]);

		clear_to_color(page[active_page], makecol(0, 0, 0));
		
		set_trans_blender(0, 0, 0, alpha);
		draw_trans_sprite(page[active_page], sprite, space_w, space_h);
		
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
		
		alpha = (int)(((float)(timer-t_start))*10);
	}
	
	alpha = 255;
	
	if(keypressed()) {
		destroy_bitmap(sprite);
			
		return active_page;
	}
	
	acquire_bitmap(page[active_page]);
	clear_bitmap(page[active_page]);
	
	clear_to_color(page[active_page], makecol(0, 0, 0));
		
	set_trans_blender(0, 0, 0, alpha);
	draw_trans_sprite(page[active_page], sprite, space_w, space_h);
	
	rest(1000);
	
	if(keypressed()) {
		destroy_bitmap(sprite);
			
		return active_page;
	}
		
	clear_to_color(page[active_page], makecol(0, 0, 0));
	draw_trans_sprite(page[active_page], sprite, space_w, space_h);
	
	textout_centre_ex(page[active_page], font_msg, PRESS_ENTER_MSG, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1); // text prompt
	
	rest(1000);
	
	t_start = timer;
	i = FALSE;
	while(TRUE) {
		if(keypressed()) {
			destroy_bitmap(sprite);
			
			return active_page;
		}
		
		acquire_bitmap(page[active_page]);
		clear_bitmap(page[active_page]);

		clear_to_color(page[active_page], makecol(0, 0, 0));
		
		r = 155-fixtoi(fixcos(itofix(timer-t_start)*1.5)*100);
		g = 128+fixtoi(fixcos(itofix(timer-t_start)/2.5)*127);
		b = 170-fixtoi(fixcos(itofix(timer-t_start)/3.5)*85);
		alpha = 175+fixtoi(fixcos(itofix(timer-t_start)*2)*80);
		
		set_trans_blender(r, g, b, alpha);
		draw_lit_sprite(page[active_page], sprite, space_w, space_h, 255-alpha);
		
		if((timer - t_tick) >= 10) {
			t_tick = timer;
			switch(i) {
				case TRUE: 
					i = FALSE;
					break;
				case FALSE:
					i = TRUE;
					break;
			}
		}
		if(i)
			textout_centre_ex(page[active_page], font_msg, PRESS_ENTER_MSG, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1); // text prompt
		
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
	return active_page;
}
#endif /* _NO3BUF */
