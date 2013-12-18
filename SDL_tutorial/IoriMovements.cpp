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

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit ) {

		Utils::clear();

		SDL_Texture * texture = Utils::loadTexture("images/iori-stand.png");

		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {

			//User requests quit
			if( e.type == SDL_QUIT )
				quit = true;
		}

		Utils::draw(texture);
		Utils::present();
	}

	//Free resources and close SDL
	close();

	return 0;
}