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
	Utils::quit();
}

int main( int argc, char* args[] ) {

	//Start up SDL and create window
	init();

	//Main loop flag
	bool quit = false;



	int x = 0;
	int y = 0;
	int moveSpeed = 10;
	SDL_Texture * texture = Utils::loadTexture("images/iori-stand.png");

	//Event handler
	SDL_Event e;
	bool draw = false;

	//While application is running
	while( !quit ) {

		draw = false;

		//Handle events on queue
		if (SDL_PollEvent(&e) == 0)
			continue;

		//User requests quit
		if ( e.type == SDL_QUIT ) {

			quit = true;
			break;

		} else if ( e.type == SDL_KEYDOWN ) {

			if ( e.key.keysym.sym == SDLK_UP ) {

				y -= moveSpeed;
				draw = true;

			} else if ( e.key.keysym.sym == SDLK_DOWN ) {

				y += moveSpeed;
				draw = true;

			} else if ( e.key.keysym.sym == SDLK_LEFT ) {

				x -= moveSpeed;
				draw = true;

			} else if ( e.key.keysym.sym == SDLK_RIGHT ) {

				x += moveSpeed;
				draw = true;
			}

			if (draw) {

				Utils::clear();
				Utils::draw(texture, x, y);
				Utils::present();
			}

			printf("%d %d\n", x, y);
		}

		if (!quit) {

			Utils::clear();
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}