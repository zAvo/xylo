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


#ifndef _HEADER_MACROS
#define _HEADER_MACROS

/* Assert macro */
#define 	__ASSERT( _cond, _errtype ) {				\
			if ( !(_cond) ) {				\
			printf _errtype;				\
			printf("\n");					\
			assert( _cond );				\
}						\
}

/* Calculation macros */
#define		COLORVAL(t)		(int)(255-12.75*(float)t)
#define		__SPACE(n)		(int)((float)SCREEN_W/(float)(4+8.5*n))
#define		BAR_TOP			(int)((float)SCREEN_H*0.925)
#define		BAR_BOTTOM		(int)((float)SCREEN_H*0.94375)
#define		TEXT_BAR_HEIGHT		(int)((float)SCREEN_H*0.95625)
#define		RADIUS(bar)		(int)(((float)(bar[1].min.x - bar[0].max.x))*0.7)
#define		HALF_BAR_SIZE(bar)	(int)(((float)(bar[0].max.x - bar[0].min.x))*0.5)
#define		IS_UINT_UNDERFLOW(x)	(x > 100000) ? TRUE : FALSE



#endif /* _HEADER_MACROS */
