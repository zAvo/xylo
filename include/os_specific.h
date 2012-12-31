#ifndef _OS_SPECIFIC
#define _OS_SPECIFIC

#ifdef WIN32
#include <wiiuse.h>

#define		GFX_DRIVER		GFX_DIRECTX
#define		DIGI_DRIVER		DIGI_DIRECTAMX(0)
#elif linux /* WIN32 */
#include "wiiuse.h"

extern void *allegro_icon;

#define		GFX_DRIVER		GFX_XWINDOWS_FULLSCREEN
#define		DIGI_DRIVER		DIGI_ALSA
#else /* linux */
#include "wiiuse.h"

extern void *allegro_icon;

#define		GFX_DRIVER		GFX_QUARTZ_FULLSCREEN
#define		DIGI_DRIVER		DIGI_CORE AUDIO
#endif /* MAC OSX */

#endif /* _OS_SPECIFIC */
