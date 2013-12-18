#include <string>
#include <iostream>
#if defined(_MSC_VER)
#include <SDL.h>
#endif

/**
* Lesson 2: Don't Put Everything in Main
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/

void logSDLError(ostream &os, const string &msg) {
	os << msg << " error: " << SDL_GetError() << endl;
}

void logSDLError(const string &msg) {
	logSDLError(cout, msg);
}

/**
*  \brief Copy full texture to the current rendering target.
*
*  \param renderer The renderer which should copy parts of a texture.
*  \param texture The source texture.
*  \param dstrect   A pointer to the destination rectangle, or NULL for the
*                   entire rendering target.
*
*  \return 0 on success, or -1 on error
*/

int SDL_RenderCopyFullTexture(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * dstrect) {

	return SDL_RenderCopy(renderer, texture, NULL, dstrect);
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param renderer The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/


SDL_Texture* loadTexture(SDL_Renderer *renderer, const string &file) {

	SDL_Texture *texture = nullptr;

	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {

		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);

		SDL_FreeSurface(loadedImage);

		//Make sure converting went ok too
		if (texture == nullptr)
			logSDLError("CreateTextureFromSurface");

	} else {

		logSDLError("LoadBMP");
	}

	return texture;
}
/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param texture The source texture we want to draw
* @param renderer The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
*/
void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y){

	//Setup the destination rectangle to be at the position we want
	SDL_Rect target;
	target.x = x;
	target.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);
	SDL_RenderCopyFullTexture(renderer, texture, &target);
}

int main2(int argc, char** argv){
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError("SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError("CreateWindow");
		return 2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		logSDLError("CreateRenderer");
		return 3;
	}

	//The textures we'll be using
	SDL_Texture *background = loadTexture(renderer, "background1.bmp");
	SDL_Texture *image = loadTexture(renderer, "smile.bmp");

	//Make sure they both loaded ok
	if (background == nullptr || image == nullptr)
		return 4;

	//Clear the window
	SDL_RenderClear(renderer);

	//Get the width and height from the texture so we know how much to move x,y by to tile it correctly
	int backgroundWidth, backgroundHeight;
	SDL_QueryTexture(background, NULL, NULL, &backgroundWidth, &backgroundHeight);

	//We want to tile our background so draw it 4 times
	renderTexture(renderer, background, 0, 0);
	renderTexture(renderer, background, backgroundWidth, 0);
	renderTexture(renderer, background, 0, backgroundHeight);
	renderTexture(renderer, background, backgroundWidth, backgroundHeight);

	//Draw our image in the center of the window
	//We need the foreground image's width to properly compute the position
	//of it's top left corner so that the image will be centered
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(renderer, image, x, y);

	//Update the screen
	SDL_RenderPresent(renderer);
	SDL_Delay(4000);

	//Destroy the various items
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
