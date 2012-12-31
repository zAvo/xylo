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
/*
#ifndef WIN32
extern void *allegro_icon;
#endif
*/

/* Timer interrupt handler */
volatile int timer = 0;
void inc_timer(void)
{
	timer++;
}
END_OF_FUNCTION(inc_timer)

/* Filter (gfx,w,h,bpp) quadruplets to show them in config box only if w>=600 */
int filter(int gfx, int w, int h, int bpp) {
	return (w>=600) ? 0 : 1;
}

/* Main starts here */
int main(int argc, char *argv[]) {
	int w, h, gfx, bpp;
	
#ifndef _NO3BUF
	int i;
	BITMAP *page[3];
#endif /* _NO3BUF */
	
	/* Initializes Allegro */
	if (allegro_init() != 0) {
		fprintf(stderr, "Unable to initialize Allegro\n");
		return 1;
	}

	install_keyboard();
	install_mouse();
	install_timer();
	
	/* Setup */
	if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		return 1;
	}
	set_palette(desktop_palette);
	
	// Default datas
	gfx = GFX_DRIVER;
	w = DEFAULT_W;
	h = DEFAULT_H;
	bpp = DEFAULT_BPP;

	// Setup interface, using filter procedure to show only quadruplets with width >= 600
	if (!gfx_mode_select_filter(&gfx, &w, &h, &bpp, filter))
		return 0;
	/* End Setup */

	/* Initializes Screen mode with setup datas */
	set_color_depth(bpp);
	if (set_gfx_mode(gfx, w, h, 0, 0) != 0) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		return 1;
	}
	
	/* Initializes Sound System */
	if(detect_digi_driver(DIGI_DRIVER) > 0) {
		if (install_sound(DIGI_DRIVER, MIDI_NONE, NULL) != 0) {
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Error initialising sound system\n%s\n", allegro_error);
			return 1;
		}
	}
	else if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Error initialising sound system\n%s\n", allegro_error);
			return 1;
		}
	
#ifdef _NO3BUF
	single_buffer();

	return 2;
#else /* _NO3BUF */
	/* If triple buffering isn't available, try to enable it */
	if (!(gfx_capabilities & GFX_CAN_TRIPLE_BUFFER)) {
		enable_triple_buffer();
	}

	/* If that didn't work, give up and start simulate double buffering */
	if (!(gfx_capabilities & GFX_CAN_TRIPLE_BUFFER)) {
		single_buffer();
		
		return 2;
	}

	/* Allocate three sub bitmaps to access pages of the screen */
	for(i=0;i<3;i++) {
		page[i] = create_video_bitmap(SCREEN_W, SCREEN_H);
		if (!page[i]) {
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Unable to create three video memory pages.\nCan allocate only %d video memory pages.\n", i+1);
			return 1;
		}
	}
	
	/* Start triple buffering */
 	triple_buffer(page);
	
	for(i=0;i<3;i++)
		destroy_bitmap(page[i]);
	
	return 3;

#endif /* _NO3BUF */
	
}
END_OF_MAIN()
