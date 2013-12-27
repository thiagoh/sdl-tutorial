/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <sdl/SDL.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include "Conf.h"
#include "timer.h"
#include "Character.h"
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

	SDL_Color blueColor;
	blueColor.a = 255;
	blueColor.r = 0;
	blueColor.g = 0;
	blueColor.b = 255;

	SDL_Color whiteColor;
	whiteColor.a = 255;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;

	Character iori(LookingTo::RIGHT, 400, BOTTOM_BOUNDARY_Y);
	Utils::addSpriteState(&iori, 0, "images/iori-stand.png", redColor, true);
	Utils::addSpriteState(&iori, 1, "images/iori-walking.png", redColor, true);
	Utils::addSpriteState(&iori, 2, "images/iori-strong-kick.png", redColor, false);

	iori.setState(0);

	Character iori2(LookingTo::RIGHT, 100, BOTTOM_BOUNDARY_Y);
	Utils::addSpriteState(&iori2, 0, "images/iori-stand.png", redColor, true);
	Utils::addSpriteState(&iori2, 1, "images/iori-walking.png", redColor, true);
	Utils::addSpriteState(&iori2, 2, "images/iori-strong-kick.png", redColor, false);

	iori2.setState(0);

	iori.setInFrontOf(&iori2);
	iori2.setInFrontOf(&iori);

	uint32_t lastDrawT = -1;

	//Event handler
	SDL_Event e;
	bool draw = false;

	SDL_EventState(SDL_KEYUP, SDL_IGNORE);

	int a = 0;

	//While application is running
	while( !quit ) {

		//Start the frame timer
		fps.start();

		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		bool isAnimating = iori.isAnimating();

		//User requests quit

		if (isAnimating && iori.isAnimationFinished())
			iori.setState(0);

		if (isAnimating) {

		} else {

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

			if ( keys[SDL_SCANCODE_A] ) {

				iori.setState(2);
			}

			if (!iori.isAnimating() && !keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT] ) 
				iori.setState(0);
		}

		Utils::clear();

		printf("index: %d\n", iori.getIndex());

		//Utils::draw(Utils::loadFromSurface(iori.getBitmap()), iori.getDrawX(), iori.getDrawY());

		iori.draw();
		iori2.draw();

		Utils::draw(Utils::loadFromSurface(iori.getBitmap()), iori.getDrawX(), iori.getDrawY(), &(iori.currentSprite().getClip()), 0.0f, iori.getDrawFlags());
		Utils::drawLine(iori.getDrawX(), iori.getDrawY(), iori.getDrawX(), iori.getDrawY() - 10, blueColor);
		Utils::drawLine(iori.getX(), iori.getDrawY() - 10, iori.getX(), iori.getDrawY() - 20, redColor);

		Utils::draw(Utils::loadFromSurface(iori2.getBitmap()), iori2.getDrawX(), iori2.getDrawY(), &(iori2.currentSprite().getClip()), 0.0f, iori2.getDrawFlags());
		Utils::drawLine(iori2.getDrawX(), iori2.getDrawY(), iori2.getDrawX(), iori2.getDrawY() - 10, blueColor);
		Utils::drawLine(iori2.getX(), iori2.getDrawY() - 10, iori2.getX(), iori2.getDrawY() - 20, redColor);

		std::stringstream sstm;
		sstm << "iori1: drawx = " << iori.getDrawX() << ", drawy = " << iori.getDrawY() << " x = " << iori.getX() << ", y = " << iori.getY()
			<< " maxWidth = " << iori.getMaxWidth() << " curWidth = " << iori.getBody().getWidth();
		Utils::draw(Utils::renderText(sstm.str(), "SourceSansPro-Regular.ttf", whiteColor, 14), 10, 10);

		sstm.str("");
		sstm.clear();
		sstm << "iori2: drawx = " << iori2.getDrawX() << ", drawy = " << iori2.getDrawY() << " x = " << iori2.getX() << ", y = " << iori2.getY()
			<< " maxWidth = " << iori2.getMaxWidth() << " curWidth = " << iori2.getBody().getWidth();
		Utils::draw(Utils::renderText(sstm.str(), "SourceSansPro-Regular.ttf", whiteColor, 14), 10, 30);

		Utils::present();

		iori.nextSpriteCycling();
		iori2.nextSpriteCycling();

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