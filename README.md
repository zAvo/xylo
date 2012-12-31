Xylo

Copyright 2008, 2009 Marco Mandrioli, Alberto Vespignani

This file is part of Xylo.

Xylo is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Xylo is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Xylo.  If not, see <http://www.gnu.org/licenses/>.


1. Intro
2. Requirements
3. Installation and Usage
4. Notes on making Xylo
5. Manual
6. Disclaimer


--------------------------
1. Intro
--------------------------

Xylo is a simulation software that emulates a vibraphone, a musical instrument
that belongs to the xylophone's percussion family. Vibraphone is nearly the same
as xylophone and marimba, but it uses aluminium bars instead of wood bars.

Xylo is developed under Linux, between Pardus (Marco) and Ubuntu (Alberto).

'Xylo' name is an abbreviation of xylophone.

The project was conceived in Marco Mandrioli's mind after he saw headtracking
video from Johnny Lee. He wanted to create a program that uses Wiimote and its
IR sensor to simulate a percussion instrument. So he started to search a library
to interact with Wiimote, and he found Wiuuse.
He decided to use Allegro for Xylo, because it's a beautiful programming library
he tried to use in 2007 in order to create a shoot'em up (now it's discontinued).

Then he asked to Alberto to do the project together, and he sadly accepted.


--------------------------
2. Requirements
--------------------------

In order to play Xylo you need a Bluetooth adapter, a Wiimote, and at least an
infrared LED (two is better to simulate the xylophone's sticks). You may use
candles or maybe lighters instead, because the fire (and heat generally) emits
infrared, but be aware that fire is dangerous, and surely you can't move candles
or lighters the same way as sticks with an infrared led at the top :-).


--------------------------
3. Installation and Usage
--------------------------

- Linux
--------------------------

To compile Xylo from sourcecode open a shell window, go to Xylo's folder and type

  make

Now simply run Xylo executable in the main folder. If you have Xylo binaries
and you have not Allegro and/or Wiiuse installed, run start.sh instead.
Starting the game will pop-up a window where you can select screen driver,
screen resolution, color quality, and even choose if you want Xylo to run
windowed or in fullscreen mode (in the driver selection).

After the introduction you are prompted to press (1) and (2) buttons simultaneously
on the Wiimote and wait for it to connect to computer.

Enjoy!

- Windows
--------------------------

Simply run Xylo.exe, which will pop-up a window where you can select screen
driver, screen resolution, color quality, and even choose if you want Xylo to
run windowed or in fullscreen mode (in the driver selection).

NOTE: You need to connect the WiiMote to the PC bluetooth BEFORE starting
Xylo.exe

Enjoy!


--------------------------
4. Notes on making Xylo
--------------------------

To develop this software, other than Allegro and Wiiuse libraries, we used:
	-SVG (yes, SVG :-P) to make Xylo logo
	-BATIK to convert Xylo logo from SVG to .tif
	-GIMP to convert Xylo logo from .tif to .tga, to make Wiiuse logo, Allegro logo,
		"Released under GPLv3" logo and some other graphics
	-Richard Sanders's GUS patches from Allegro site to obtain the vibraphone's wavetable
	-LMMS to create .wav files from a midi file played with PAT sounds
	-Audacity to edit .wav files generated with LMMS
	_Visual Studio 2005 & 2008 to create the solutions needed for
		building Xylo on Windows
	_Inno Setup Compiler to create the setup program for Xylo for Windows

Xylo logo is drawn with Curlz MT font, Wiiuse logo is drawn with Continuum font,
the in-game font is Baskerville, converted from ttf to pcx using ttf2pcx.

Xylo logo created by Marco Mandrioli
Wiiuse logo, Allegro logo, and "released under GPLv3" logo created by Marco Mandrioli
GPLv3 logo is "property" of Free Software Foundation (FSF)

Developed under: Pardus Linux and Ubuntu Linux.

Xylo for Windows, Xylo for Windows setup, MSVC projects developed under:
	Windows XP 32-bit, Windows Vista 64-bit and Windows 7 64-bit


--------------------------
5. Manual
--------------------------

About Allegro and Wiiuse manuals, can be found on the web, or go to:

Allegro		www.allegro.cc
Wiiuse		www.wiiuse.net


--------------------------
6. Disclaimer
--------------------------

The software is released under GPLv3. You can read more about that at

http://www.gnu.org/licenses/gpl-3.0.html
