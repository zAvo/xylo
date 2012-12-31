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


#ifndef _HEADER_CONSTS
#define _HEADER_CONSTS

/* Uncomment this to force double buffering */
#define _NO3BUF

/* Uncomment this to set game language in italian */
// #define _LOCALE_ITA

#ifdef _LOCALE_ITA
/* Error strings */
#define		ERROR_MEM_ALLOC			("Allocazione della memoria non riuscita")
#define		ERROR_NOT_ENOUGH_SOUNDS		("Non sono definiti abbastanza files sonori")
#define		ERROR_CANT_LOAD_SAMPLE(f)	("Impossibile caricare il file %s", f)
#define		ERROR_CANT_LOAD_FONT(f)		("Impossibile caricare il font %s", f)
#define		ERROR_CANT_LOAD_IMAGE(f)	("Impossibile caricare l'immagine %s", f)
#define		ERROR_CANT_ALLOC_VOICE(n)	("Impossibile allocare più di %d voci hardware", n)
#define		ERROR_CANT_OPEN_WIIMOTE		("Impossibile connettersi al Wiimote")
#define 	ERROR_WHILE_CALIBRATING		("Calibrazione fallita")

/* Message strings */
#define		WIIMOTE_CONNECTION_MSG		("Premi i tasti 1 e 2 sul telecomando per avviare il programma.")
#define		PRESS_ENTER_MSG			("Premi invio per iniziare.")

/* Calibration strings */
#define		WIIMOTE_CAL_ASX			("Calibrazione: Bacchetta in alto a sinistra e premi invio.")
#define		WIIMOTE_CAL_BDX			("Calibrazione: Bacchetta in basso a destra e premi invio.")

#else /* _LOCALE_ITA */
/* Error strings */
#define		ERROR_MEM_ALLOC			("Memory allocation failed")
#define		ERROR_NOT_ENOUGH_SOUNDS		("Not enough sound files")
#define		ERROR_CANT_LOAD_SAMPLE(f)	("Can't load file %s", f)
#define		ERROR_CANT_LOAD_FONT(f)		("Can't load font %s", f)
#define		ERROR_CANT_LOAD_IMAGE(f)	("Can't load image %s", f)
#define		ERROR_CANT_ALLOC_VOICE(n)	("Can't allocate more than %d hardware voices", n)
#define		ERROR_CANT_OPEN_WIIMOTE		("Can't connect to Wiimote")
#define 	ERROR_WHILE_CALIBRATING		("Calibration failed")

/* Message strings */
#define		WIIMOTE_CONNECTION_MSG		("Press buttons 1 and 2 on the remote to start the program.")
#define		PRESS_ENTER_MSG			("Press enter to start.")

/* Calibration strings */
#define		WIIMOTE_CAL_ASX			("Calibration: Rod upper left and press enter.")
#define		WIIMOTE_CAL_BDX			("Calibration: Rod lower right and press enter.")

#endif /* _LOCALE_ITA */

/* Numeric constants */
#define		DEFAULT_W		1280
#define		DEFAULT_H		800
#define		DEFAULT_BPP		32
#define		NUM_BARS		14
#define		MAX_IR_DOTS		2
#define		TICKS_TO_BLACK		20
#define		NUM_MAX_SOUNDS		15
#define		NUM_MAX_FONTS		7

/* Initialization constants */
#define		NOTES			{"C", "D", "E", "F", "G", "A", "B"}
#define		SOUND_FILES		{"sounds/C1.wav", "sounds/D1.wav", "sounds/E1.wav", "sounds/F1.wav", "sounds/G1.wav", "sounds/A1.wav", "sounds/B1.wav", "sounds/C2.wav", "sounds/D2.wav", "sounds/E2.wav", "sounds/F2.wav", "sounds/G2.wav", "sounds/A2.wav", "sounds/B2.wav", "sounds/C2.wav"}
#define		FONTS			{"fonts/bask20.pcx", "fonts/bask18.pcx", "fonts/bask16.pcx", "fonts/bask14.pcx", "fonts/bask12.pcx", "fonts/bask11.pcx", "fonts/bask10.pcx"}

#endif /* _HEADER_CONSTS */
