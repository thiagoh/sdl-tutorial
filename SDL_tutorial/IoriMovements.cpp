/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

#include "utils.h"

void init() {

	try {

		Utils::init("Meu jogo");

	} catch(exception e) {

		printf(e.what());
		exit(1);
	}
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

int main( int argc, char* args[] ) {

	//Start up SDL and create window
	if( !init() ) {

		printf( "Failed to initialize!\n" );
		exit(1);
	}

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

	//Free resources and close SDL
	close();

	return 0;
}