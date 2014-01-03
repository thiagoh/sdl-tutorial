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

	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);

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

int Utils::drawLine(int x1, int y1, int x2, int y2) {

	return SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
}

int Utils::drawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {

	Uint8 oldr, oldg, oldb, olda;
	SDL_GetRenderDrawColor(_renderer.get(), &oldr, &oldg, &oldb, &olda);
	SDL_SetRenderDrawColor(_renderer.get(), r, g, b, a);

	int v = SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);

	SDL_SetRenderDrawColor(_renderer.get(), oldr, oldg, oldb, olda);

	return v;
}

int Utils::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {

	return drawLine(x1, y1, x2, y2, color.r, color.g, color.b, color.a);
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

void Utils::addSpriteDefaultState(Character* character, const char * filename, SDL_Color delimiterColor) {

	vector<KeyMatcher*> events;
	addSpriteState(character, filename, delimiterColor, true, events, false);
}

void Utils::addSpriteState(Character* character, const char * filename, SDL_Color delimiterColor, KeyMatcher* _event, bool stoppable) {

	vector<KeyMatcher*> events;
	events.push_back(_event);
	addSpriteState(character, filename, delimiterColor, events, stoppable);
}

void Utils::addSpriteState(Character* character, const char * filename, SDL_Color delimiterColor, vector<KeyMatcher*> events, bool stoppable) {

	addSpriteState(character, filename, delimiterColor, false, events, stoppable);
}

void Utils::addSpriteState(Character* character, const char * filename, SDL_Color delimiterColor, bool _default, vector<KeyMatcher*> events, bool stoppable) {

	SDL_Surface* bitmap = IMG_Load(filename);

	SDL_PixelFormat* format = bitmap->format;

	Uint32* pixels = (Uint32*) bitmap->pixels;
	Uint32 pixel, lastPixel = 0;
	Uint32 delimiterColorPixel = SDL_MapRGBA(format, delimiterColor.r, delimiterColor.g, delimiterColor.b, delimiterColor.a);

	std::vector<SpritePiece> spriteVector;
	int lastSource = 0;

	for (int i = 0; i < bitmap->w; i++) {

		pixel = pixels[i];

		if (pixel != lastPixel) {

			if (pixel == delimiterColorPixel) {

				i++; // current pixel is the red one, so, advance to next pixel

				if (spriteVector.empty()) {

					spriteVector.push_back(SpritePiece(bitmap, 0, 0, i, bitmap->h));

				} else {

					spriteVector.push_back(SpritePiece(bitmap, lastSource, 0, i - lastSource, bitmap->h));
				}

				lastSource = i;
			}

		} else if(i == bitmap->w - 1) {

			spriteVector.push_back(SpritePiece(bitmap, lastSource, 0, i - lastSource, bitmap->h));
		}

		lastPixel = pixel;
	}

	SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGBA(bitmap->format, delimiterColor.r, delimiterColor.g, delimiterColor.b, delimiterColor.a));
	//al_convert_mask_to_alpha(bitmap, al_map_rgba(255, 0, 0, 255));

	if (_default) {

		character->addDefaultState(bitmap, spriteVector);

	} else {

		character->addState(bitmap, spriteVector, events, stoppable);
	}
}