/*
Simple Software Rasterising Engine

Copyright (c) 2014 Neil Richardson (neilogd)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef __SSRE_TYPES_H__
#define __SSRE_TYPES_H__

#include <assert.h>


/**
 * Basic types.
 */
#if defined( WINDOWS )
typedef unsigned _int64					u64;
typedef unsigned int					u32;
typedef	unsigned short					u16;
typedef unsigned char					u8;

typedef signed _int64					s64;
typedef signed int						s32;
typedef	signed short					s16;
typedef signed char						sS8;
#endif


#if defined( PLATFORM_GBA )
typedef	unsigned char			u8;		/**< Unsigned 8 bit value	*/
typedef	unsigned short int		u16;	/**< Unsigned 16 bit value	*/
typedef	unsigned int			u32;	/**< Unsigned 32 bit value	*/
typedef	unsigned long long		u64;	/**< Unsigned 64 bit value	*/
typedef	signed char				s8;		/**< Signed 8 bit value	*/
typedef	signed short int		s16;	/**< Signed 16 bit value	*/
typedef	signed int				s32;	/**< Signed 32 bit value	*/
typedef	signed long long		s64;	/**< Signed 64 bit value	*/
typedef	volatile u8				vu8;	/**< volatile Unsigned 8 bit value	*/
typedef	volatile u16			vu16;	/**< volatile Unigned 16 bit value	*/
typedef	volatile u32			vu32;	/**< volatile Unsigned 32 bit value	*/
typedef	volatile s8				vs8;	/**< volatile Signed 8 bit value	*/
typedef	volatile s16			vs16;	/**< volatile Signed 8 bit value	*/
typedef	volatile s32			vs32;	/**< volatile Signed 8 bit value	*/


//#include <gba.h>
#endif 

#endif

