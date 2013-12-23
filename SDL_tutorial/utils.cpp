#include <string>
#include <stdexcept>
#include <memory>

#if defined(_MSC_VER)
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <sdl/SDL_ttf.h>
#endif

#include "utils.h"

using namespace std;

//Initialize the unique_ptr's deleters here
unique_ptr<SDL_Window, void (*)(SDL_Window*)> Utils::_window = unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Utils::_renderer = unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);

//other static members
SDL_Rect Utils::mBox;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void Utils::init(string title) {

	//initialize all SDL subsystems

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw runtime_error("SDL Init Failed");

	if (TTF_Init() == -1)
		throw runtime_error("TTF Init Failed");

	//Setup our window
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = SCREEN_WIDTH;
	mBox.h = SCREEN_HEIGHT;

	//Create our window
	_window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  mBox.w, mBox.h, SDL_WINDOW_SHOWN));

	//Make sure it created ok
	if (_window == nullptr)
		throw runtime_error("Failed to create window");

	//Create the _renderer
	_renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	//Make sure it created ok
	if (_renderer == nullptr)
		throw runtime_error("Failed to create _renderer");
}

void Utils::quit() {

	TTF_Quit();
	SDL_Quit();
}

void Utils::draw(SDL_Texture *texture, int x, int y, SDL_Rect *clip, float angle, SDL_RendererFlip flip) {

	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;

	if (clip == nullptr) {

		SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

	} else {

		dstRect.w = clip->w;
		dstRect.h = clip->h;
	}


	//Draw the texture
	SDL_RenderCopyEx(_renderer.get(), texture, clip, &dstRect, angle, NULL, flip);
}

void Utils::draw(SDL_Texture *texture, SDL_Rect *dstRect, SDL_Rect *clip, float angle, SDL_Point* center, SDL_RendererFlip flip) {

	if (dstRect == nullptr) {

		dstRect = new SDL_Rect();
		dstRect->x = 0;
		dstRect->y = 0;

		if (clip == nullptr) {

			SDL_QueryTexture(texture, NULL, NULL, &(dstRect->w), &(dstRect->h));

		} else {

			dstRect->w = clip->w;
			dstRect->h = clip->h;
		}
	}

	if (center == nullptr) {

		//Convert pivot pos from relative to object's center to screen space
		center = new SDL_Point();
		center->x = dstRect->w / 2;
		center->y = dstRect->h / 2;
	}

	//Draw the texture
	SDL_RenderCopyEx(_renderer.get(), texture, clip, dstRect, angle, center, flip);
}

SDL_Texture* Utils::loadTexture(const char* filepath) {

	return loadTexture(string(filepath));
}

SDL_Texture* Utils::loadTexture(const string &file) {

	SDL_Texture* texture = IMG_LoadTexture(_renderer.get(), file.c_str());

	if (texture == nullptr)
		throw runtime_error("Failed to load image: " + file + ". " + IMG_GetError());

	return texture;
}

SDL_Texture* Utils::renderText(const char* message, const char* fontFile, SDL_Color color, int fontSize) {

	return renderText(string(message), string(fontFile), color, fontSize);
}

SDL_Texture* Utils::renderText(const string &message, const string& fontFile, SDL_Color color, int fontSize) {

	//Open the font

	TTF_Font *font = nullptr;

	font = TTF_OpenFont(fontFile.c_str(), fontSize);

	if (font == nullptr)
		throw runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns

	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer.get(), surf);

	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

Uint32 Utils::getPixel32( SDL_Surface *surface, int x, int y ) {

	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Get the requested pixel
	return pixels[ ( y * surface->w ) + x ];
}

void Utils::putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel) {
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Set the pixel
	pixels[ ( y * surface->w ) + x ] = pixel;
}

SDL_Texture* Utils::loadFromSurface(SDL_Surface* surface) {

	return SDL_CreateTextureFromSurface(_renderer.get(), surface);
}

void Utils::clear() {
	SDL_RenderClear(_renderer.get());
}

void Utils::present() {
	SDL_RenderPresent(_renderer.get());
}

SDL_Rect Utils::getBox() {
	return mBox;
}
