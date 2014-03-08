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

int main( int argc, char* argv[] )
{
	int width = 640;
	int height = 480;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	u32* pixels = (u32*)malloc( width * height * sizeof( u32 ) );
	u32 shouldQuit = 0;
	SSRE_Fixed_t fixedA = SSRE_Fixed_FromFloat( 100.0f );
	SSRE_Fixed_t fixedB = SSRE_Fixed_Sqrt( fixedA );
	float val = 0.0f;
	SSRE_Vec4_t vecA = 
	{
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
	};

	SSRE_Vec4_t vecB = 
	{
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 1.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
		SSRE_Fixed_FromFloat( 0.0f ),
	};

	//SSRE_Vec4_t vecC;

	//SSRE_Vec4_Reflect( &vecC, &vecA, &vecB );
	//val = SSRE_Fixed_ToFloat( vecA.x );

	window = SDL_CreateWindow( "Simple Software Rasterising Engine SDL2 Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0 );
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height );

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

		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof ( u32 ));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	while( !shouldQuit );

	free( pixels );

	return 0;
}
