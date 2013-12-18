/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Texture* loadTexture( char * path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Renderer *renderer = NULL;

bool init() {

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;

	} else {

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {

			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;

		} else {

			//Get window surface
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == nullptr) {
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
		}
	}

	return success;
}

void close() {

	//Destroy the various items

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);

	//Quit SDL subsystems
	SDL_Quit();
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(char* filepath) {

	SDL_Texture *texture = nullptr;

	//Load the image

	SDL_Surface *loadedImage = SDL_LoadBMP(filepath);

	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {

		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);

		SDL_FreeSurface(loadedImage);
	}

	return texture;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() ) {

		printf( "Failed to initialize!\n" );

	} else {

		SDL_Texture * texture = loadTexture("stretch.bmp");

		//Load media

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
					quit = true;
			}

			//Clear the window
			SDL_RenderClear(renderer);

			//Setup the destination rectangle to be at the position we want
			SDL_Rect dst;
			dst.x = 0;
			dst.y = 0;
			dst.w = SCREEN_WIDTH;
			dst.h = SCREEN_HEIGHT;
			//Query the texture to get its width and height to use
			//SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

			SDL_RenderCopy(renderer, texture, NULL, &dst);

			//Update the screen
			SDL_RenderPresent(renderer);

			//Update the surface
			//SDL_UpdateWindowSurface( gWindow );
		}

		SDL_DestroyTexture(texture);
	}

	//Free resources and close SDL
	close();

	return 0;
}