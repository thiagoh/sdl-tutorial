/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <sdl/SDL.h>
#include <stdio.h>
#include <string>
#include "timer.h"
#include "Sprite.h"
#include "SpriteUtil.h"
#include "utils.h"

//The frames per second
const int FRAMES_PER_SECOND = 14;

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

	//Keep track of the current frame
	int frame = 0;

	//Whether or not to cap the frame rate
	bool cap = true;

	//The frame rate regulator
	Timer fps;

	int x = 0;
	int y = 0;
	int moveSpeed = 10;
	SDL_Texture * texture = Utils::loadTexture("images/iori-stand.png");

	SDL_Color redColor;
	redColor.a = 255;
	redColor.r = 255;
	redColor.g = 0;
	redColor.b = 0;

	Sprite iori(0, 0);
	Utils::addSpriteState(&iori, 0, "images/iori-stand.png", redColor);
	Utils::addSpriteState(&iori, 1, "images/iori-walking.png", redColor);

	iori.setState(0);

	uint32_t lastDrawT = -1;

	//Event handler
	SDL_Event e;
	bool draw = false;

	SDL_EventState(SDL_KEYUP, SDL_IGNORE);

	//While application is running
	while( !quit ) {

		//Start the frame timer
		fps.start();

		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		//User requests quit

		if ( keys[SDL_SCANCODE_UP] ) {

			iori.decY(moveSpeed);
		} 

		if ( keys[SDL_SCANCODE_DOWN] ) {

			iori.incY(moveSpeed);
		} 

		if ( keys[SDL_SCANCODE_LEFT] ) {

			iori.decX(moveSpeed);
			iori.setState(1);
		} 

		if ( keys[SDL_SCANCODE_RIGHT] ) {

			iori.incX(moveSpeed);
			iori.setState(1);
		}

		if (!keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT] ) {

			iori.setState(0);
		}

		Utils::clear();

		printf("index: %d\n", iori.getIndex());

		//Utils::draw(Utils::loadFromSurface(iori.getBitmap()), iori.getX(), iori.getY());
		Utils::draw(Utils::loadFromSurface(iori.getBitmap()), iori.getX(), iori.getY(), &(iori.current().getClip()));
		Utils::present();

		iori.nextCycling();

		//Increment the frame counter
		frame++;

		//If we want to cap the frame rate
		if( ( cap == true ) && ( fps.ticks() < 1000 / FRAMES_PER_SECOND ) ) {

			//Sleep the remaining frame time
			Uint32 delay = (1000 / FRAMES_PER_SECOND) - fps.ticks();

			SDL_Delay(delay);
			//printf("delay %d\n", delay);
		}
	}

	Utils::clear();

	//Free resources and close SDL
	close();

	return 0;
}