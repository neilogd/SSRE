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

#include <SDL.h>
#include <SSRE.h>

#include <memory.h>
#include <malloc.h>
#include <math.h>

#define OUT_W ( 240 )
#define OUT_H ( 160 )
#define OUT_SCALE ( 3 )

void drawTriangle( SSRE_PixelBuffer_t* buffer, const void* points, u32 vertexType, u32 vertexStride )
{
	int x, y;
	u16* out;
	u16* outRow;
	SSRE_Vec4_t minCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxCoord = { 0, 0, 0, 0 };
	SSRE_Vec4_t minPixel = { 0, 0, 0, 0 };
	SSRE_Vec4_t maxPixel = { 0, 0, 0, 0 };
	const SSRE_Vec4_t* point0 = (const SSRE_Vec4_t*)(((char*)points));
	const SSRE_Vec4_t* point1 = (const SSRE_Vec4_t*)(((char*)points) + vertexStride);
	const SSRE_Vec4_t* point2 = (const SSRE_Vec4_t*)(((char*)points) + ( vertexStride << 1 ));
	const u16* colour = (const u16*)(point0 + 1);
	SSRE_Vec4_t cross20, cross21, cross123;
	SSRE_Vec4_t baryAStep, baryBStep;
	SSRE_Vec4_t baryRow = { 0, 0, 0, 0 };
	SSRE_Vec4_t bary = { 0, 0, 0 ,0 };
	SSRE_Vec4_t baryNrm = { 0, 0, 0 ,0 };
	
	// Calculate facing of triangle so we can cull back facing.
	SSRE_Vec4_Sub3( &cross20, point2, point0 );
	SSRE_Vec4_Sub3( &cross21, point1, point0 );
	SSRE_Vec4_Cross2( &cross123, &cross21, &cross20 );
	if( cross123.z < 0 )
	{
		return;
	}

	minCoord.x = ( ( SSRE_Fixed_Floor( SSRE_Fixed_Min3( point0->x, point1->x, point2->x ) ) >> SSRE_FIXED_PRECISION ) & 0xfffe ) << SSRE_FIXED_PRECISION;
	minCoord.y = SSRE_Fixed_Floor( SSRE_Fixed_Min3( point0->y, point1->y, point2->y ) );
	maxCoord.x = SSRE_Fixed_Max3( point0->x, point1->x, point2->x );
	maxCoord.y = SSRE_Fixed_Max3( point0->y, point1->y, point2->y );

	minCoord.x = SSRE_Fixed_Clamp( minCoord.x, 0, ( buffer->w - 1 ) << SSRE_FIXED_PRECISION );
	minCoord.y = SSRE_Fixed_Clamp( minCoord.y, 0, ( buffer->h - 1 ) << SSRE_FIXED_PRECISION );
	maxCoord.x = SSRE_Fixed_Clamp( maxCoord.x, 0, ( buffer->w - 1 ) << SSRE_FIXED_PRECISION );
	maxCoord.y = SSRE_Fixed_Clamp( maxCoord.y, 0, ( buffer->h - 1 ) << SSRE_FIXED_PRECISION );

	minPixel.x = minCoord.x >> SSRE_FIXED_PRECISION;
	minPixel.y = minCoord.y >> SSRE_FIXED_PRECISION;
	maxPixel.x = maxCoord.x >> SSRE_FIXED_PRECISION;
	maxPixel.y = maxCoord.y >> SSRE_FIXED_PRECISION;

	// Barycentric step values.
	baryAStep.x = point1->y - point2->y;
	baryAStep.y = point2->y - point0->y;
	baryAStep.z = point0->y - point1->y;
	baryBStep.x = point2->x - point1->x;
	baryBStep.y = point0->x - point2->x;
	baryBStep.z = point1->x - point0->x;

	// Set initial top left barycentric coords.
	baryRow.x = SSRE_Math_OrientationTest2( point1, point2, &minCoord );
	baryRow.y = SSRE_Math_OrientationTest2( point2, point0, &minCoord );
	baryRow.z = SSRE_Math_OrientationTest2( point0, point1, &minCoord );

	// Setup output row of pixels.
	outRow = (u16*)SSRE_PixelBuffer_Pixel( buffer, minPixel.x, minPixel.y );
	
	// Render all pixels which are in the triangle.
	for( y = minPixel.y; y <= maxPixel.y; ++y, outRow += buffer->w )
	{	
		out = outRow;
		bary = baryRow;

		for( x = minPixel.x; x <= maxPixel.x; ++x, ++out )
		{
			if( ( bary.x | bary.y | bary.z ) >= 0 )
			{
				if( ( vertexType & SSRE_VERTEX_HAS_COLOUR_16 ) != 0 )
				{
					// Compensate for some precision loss when we try to renormalise.
					baryNrm.x = bary.x >> SSRE_FIXED_HALF_PRECISION;
					baryNrm.y = bary.y >> SSRE_FIXED_HALF_PRECISION;
					baryNrm.z = bary.z >> SSRE_FIXED_HALF_PRECISION;

					// Renormalise. Approximation.
					SSRE_Vec4_FastMulScalar3( &baryNrm, &baryNrm, SSRE_Fixed_Rcp( baryNrm.x + baryNrm.y + baryNrm.z ) );				

					*out = SSRE_Math_LerpColourR5G5B5( 3, colour, vertexStride, &baryNrm.x );
				}
			}
			SSRE_Vec4_Add3( &bary, &bary, &baryAStep );
		}

		SSRE_Vec4_Add3( &baryRow, &baryRow, &baryBStep );
	}
}

static SSRE_VertexPC16T_t s_TriangleVertices[] = 
{
	// Top face.
	{ { SSRE_Fixed_FromFloat( -0.5f ), SSRE_Fixed_FromFloat( -0.5f ), SSRE_Fixed_FromFloat(  0.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  0.5f ), SSRE_Fixed_FromFloat( -0.5f ), SSRE_Fixed_FromFloat(  0.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -0.5f ), SSRE_Fixed_FromFloat(  0.5f ), SSRE_Fixed_FromFloat(  0.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
};

static SSRE_VertexPC16T_t s_CubeVertices[] = 
{
	// Top face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },

	// bottom face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555( 31,  0,  0 ), 0, 0 },

	// back face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },

	// front face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0, 31,  0 ), 0, 0 },

	// Right face.
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },

	// Left face.
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },

	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ),SSRE_Fixed_FromFloat(  1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
	{ { SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat( -1.0f ),SSRE_Fixed_FromFloat( -1.0f ), SSRE_Fixed_FromFloat(  1.0f ) }, SSRE_MATH_RGB555(  0,  0, 31 ), 0, 0 },
};

int main( int argc, char* argv[] )
{
	int i,j;
	u32 timerStart;
	u32 timerEnd;
	u32 frameCount = 0;
	u32 frameTicker = 0;
	const SSRE_VertexPC16T_t* firstVertex;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	SSRE_Mat44_t worldMat;
	SSRE_Mat44_t viewMat;
	SSRE_Mat44_t projMat;
	SSRE_Mat44_t ssMat;
	SSRE_Mat44_t clipMat;
	SSRE_MatrixStack_t matrixStack;
	SSRE_VertexProcessor_t vertexProcessor;
	SSRE_PixelBuffer_t buffer; 
	SSRE_Vec4_t halfRes = 
	{ 
		( OUT_W >> 1 ) << SSRE_FIXED_PRECISION,
		( OUT_H >> 1 ) << SSRE_FIXED_PRECISION,
		0, 
		0 
	};

	u32 shouldQuit = 0;

	SSRE_MatrixStack_Create( &matrixStack, 16 );
	SSRE_VertexProcessor_Create( &vertexProcessor, 256, SSRE_VERTEX_HAS_POSITION | 
	                                                    SSRE_VERTEX_HAS_COLOUR_16 |
	                                                    SSRE_VERTEX_HAS_UV, 
														sizeof( SSRE_VertexPC16T_t ) );
	SSRE_PixelBuffer_Create( &buffer, 2, OUT_W, OUT_H, NULL );
	SSRE_Mat44_Identity( &worldMat );
	SSRE_Mat44_Identity( &viewMat );
	SSRE_Mat44_Identity( &projMat );
	SSRE_Mat44_Identity( &clipMat );

	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, buffer.w * OUT_SCALE, buffer.h * OUT_SCALE, 0 );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
	texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_STREAMING, buffer.w, buffer.h );

	timerStart = SDL_GetTicks();
	do
	{
		SDL_Event event;

		if( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_QUIT:
				shouldQuit = 1;
				break;
			default:
				break;
			}
		}

		memset( buffer.addr, 0x0, buffer.w * buffer.h * buffer.bpp );

		// Reset vertex processor.
		SSRE_VertexProcessor_Reset( &vertexProcessor );

		// Generate screen space matrix.
		SSRE_Mat44_Identity( &ssMat );
		ssMat.rows[0].x = halfRes.x;
		ssMat.rows[1].y = halfRes.y;
		ssMat.rows[3].x = halfRes.x;
		ssMat.rows[3].y = halfRes.y;

		// Generate perspective.
		SSRE_Mat44_Perspective( &projMat, 8, SSRE_Fixed_Div( halfRes.y, halfRes.x ), SSRE_Fixed_FromFloat( 1.0f ), SSRE_Fixed_FromFloat( 10.0f ) );

		// Matrices onto stack.
		SSRE_MatrixStack_Push( &matrixStack, &ssMat );
		SSRE_MatrixStack_Push( &matrixStack, &projMat );
		SSRE_MatrixStack_Push( &matrixStack, &viewMat );

		// Draw model.
		{
			SSRE_Mat44_Rotation( &worldMat, frameTicker , frameTicker >> 3, frameTicker >> 6 );
			worldMat.rows[3].x = 0;
			worldMat.rows[3].y = 0;
			worldMat.rows[3].z = -SSRE_FIXED_ONE << 3;

			SSRE_MatrixStack_Push( &matrixStack, &worldMat );

			SSRE_MatrixStack_Get( &clipMat, &matrixStack );
			firstVertex = (SSRE_VertexPC16T_t*)SSRE_VertexProcessor_Process( &vertexProcessor, 36, s_CubeVertices, &clipMat );

			for( j = 0; j < 1; ++j )
			{
				for( i = 0; i < 12; ++i )
				{
					drawTriangle( &buffer, firstVertex + ( i * 3 ), vertexProcessor.vertexType, vertexProcessor.vertexStride );
				}
			}

			SSRE_MatrixStack_Pop( &matrixStack, 1 );
		}

		// Pop proj and view.
		SSRE_MatrixStack_Pop( &matrixStack, 3 );

		SDL_UpdateTexture(texture, NULL, buffer.addr, buffer.w * buffer.bpp );
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		++frameCount;
		frameTicker += 1;
		
		if( frameCount == 60 )
		{
			timerEnd = SDL_GetTicks();

			SDL_Log( "60 frames rendered in %u ms (%f ms per frame )\n", timerEnd - timerStart, (float)(timerEnd - timerStart) / 60.0f );

			timerStart = timerEnd;
			frameCount = 0;
		}
	}
	while( !shouldQuit );

	SSRE_MatrixStack_Destroy( &matrixStack );
	SSRE_VertexProcessor_Destroy( &vertexProcessor );
	SSRE_PixelBuffer_Destroy( &buffer );

	return 0;
}
