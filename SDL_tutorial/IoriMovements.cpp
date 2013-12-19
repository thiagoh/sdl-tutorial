/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <sdl/SDL.h>
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
	Utils::quit();
}

int main( int argc, char* args[] ) {

	//Start up SDL and create window
	init();

	//Main loop flag
	bool quit = false;

	int x = 0;
	int y = 0;
	int moveSpeed = 5;
	SDL_Texture * texture = Utils::loadTexture("images/iori-stand.png");

	uint32_t lastDrawT = -1;

	//Event handler
	SDL_Event e;
	bool draw = false;

    SDL_EventState(SDL_KEYUP, SDL_IGNORE);

	//While application is running
	while( !quit ) {

		//Handle events on queue

		uint32_t tx1 = SDL_GetTicks();

		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		draw = false;

		//User requests quit

		if ( keys[SDL_SCANCODE_UP] ) {

			y -= moveSpeed;
			draw = true;

		} 
		if ( keys[SDL_SCANCODE_DOWN] ) {

			y += moveSpeed;
			draw = true;

		} 
		if ( keys[SDL_SCANCODE_LEFT] ) {

			x -= moveSpeed;
			draw = true;
			printf("left\n");

		} 
		if ( keys[SDL_SCANCODE_RIGHT] ) {

			x += moveSpeed;
			draw = true;
			printf("right\n");
		}

		if (draw) {

			Utils::clear();
			Utils::draw(texture, x, y);
			Utils::present();
		}

		SDL_Delay(10);
	}

	Utils::clear();

	//Free resources and close SDL
	close();

	return 0;
}