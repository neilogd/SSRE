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
#ifndef __SSRE_H__
#define __SSRE_H__

#include "SSRE_Types.h"
#include "SSRE_Fixed.h"
#include "SSRE_Vec4.h"
#include "SSRE_Mat44.h"
#include "SSRE_MatrixStack.h"
#include "SSRE_Math.h"
#include "SSRE_PixelBuffer.h"
#include "SSRE_Vertex.h"
#include "SSRE_VertexProcessor.h"

/**
 * Get library version.
 * @param outMajor Pointer for where to write major version.
 * @param outMajor Pointer for where to write minor version.
 * @param outMajor Pointer for where to write revision version.
 */
void SSRE_GetVersion( int* outMajor, int* outMinor, int* outRevision );

#endif // __SSRE_H__
