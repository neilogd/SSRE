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
#ifndef __SSRE_VEC4_H__
#define __SSRE_VEC4_H__

#include "SSRE_Fixed.h"

/**
 * Fixed point type.
 */
typedef struct
{
	SSRE_Fixed_t x;
	SSRE_Fixed_t y;
	SSRE_Fixed_t z;
	SSRE_Fixed_t w;
} SSRE_Vec4_t;

/**
 * Add vec4 to another.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_Add( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Sub vec4 from another.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_Sub( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Mul vec4 by another.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_Mul( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Div vec4 by another.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_Div( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Mul vec4 by scalar.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_MulScalar( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs );


/**
 * Div vec4 by scalar.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_DivScalar( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, SSRE_Fixed_t rhs );


/**
 * Reciprocal of vec4.
 * @param out Output vector.
 * @param lhs
 */
void SSRE_Vec4_Rcp( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs );

/**
 * Dot3.
 * @param lhs
 * @param rhs
 */
SSRE_Fixed_t SSRE_Vec4_Dot3( const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Dot.
 * @param lhs
 * @param rhs
 */
SSRE_Fixed_t SSRE_Vec4_Dot( const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Cross3.
 * @param out Output vector.
 * @param lhs
 * @param rhs
 */
void SSRE_Vec4_Cross3( SSRE_Vec4_t* out, const SSRE_Vec4_t* lhs, const SSRE_Vec4_t* rhs );

/**
 * Magnitude squared3.
 * @param lhs
 */
SSRE_Fixed_t SSRE_Vec4_MagSqr3( const SSRE_Vec4_t* lhs );

/**
 * Magnitude3.
 * @param lhs
 */
SSRE_Fixed_t SSRE_Vec4_Mag3( const SSRE_Vec4_t* lhs );

/**
 * Magnitude squared4.
 * @param lhs
 */
SSRE_Fixed_t SSRE_Vec4_MagSqr( const SSRE_Vec4_t* lhs );

/**
 * Magnitude4.
 * @param lhs
 */
SSRE_Fixed_t SSRE_Vec4_Mag( const SSRE_Vec4_t* lhs );

/**
 * Normalise3.
 * @param lhs
 */
void SSRE_Vec4_Nrm3( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs );

/**
 * Normalise4.
 * @param lhs
 */
void SSRE_Vec4_Nrm( SSRE_Vec4_t* out, SSRE_Vec4_t* lhs );

#endif