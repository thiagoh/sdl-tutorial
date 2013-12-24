#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdexcept>
#include <memory>

#if defined(_MSC_VER)
#include <sdl/SDL.h>
#endif

#include "Sprite.h"

using namespace std;

/**
*  Utils management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Utils {
public:

	//The constructor and destructor don't actually do anything as the class is pure static
	Utils() {};
	~Utils() {};
	/**
	*  Initialize SDL, setup the window and renderer
	*  @param title The window title
	*/
	static void init(string title = "Window");

	///Quit SDL and destroy the window and renderer
	static void quit();


	/**
	*  Draw a SDL_Texture to the screen at dstRect with various other options
	*  @param texture The SDL_Texture to draw
	*  @param x The x coordinate of the texture
	*  @param y The y coordinate of the texture
	*  @param clip The clip to apply to the image, if desired
	*  @param angle The rotation angle to apply to the texture, default is 0
	*  @param flip The flip to apply to the image, default is none
	*/
	static void draw(SDL_Texture *texture, int x, int y, SDL_Rect *clip = NULL, float angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/**
	*  Draw a SDL_Texture to the screen at dstRect with various other options
	*  @param texture The SDL_Texture to draw
	*  @param dstRect The destination position and width/height to draw the texture with
	*  @param clip The clip to apply to the image, if desired
	*  @param angle The rotation angle to apply to the texture, default is 0
	*  @param center The x,y coordinate of the pivot, relative to (0, 0) being center of dstRect
	*  @param flip The flip to apply to the image, default is none
	*/
	static void draw(SDL_Texture *texture, SDL_Rect * dstRect =  NULL, SDL_Rect *clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*  Loads an image directly to texture using SDL_image's
	*  built in function IMG_LoadTexture
	*  @param file The image file to load
	*  @return SDL_Texture* to the loaded texture
	*/
	static SDL_Texture* loadTexture(const string &file);

	static SDL_Texture* loadTexture(const char * filepath );

	static SDL_Texture* loadFromSurface(SDL_Surface* surface);

	/**
	*  Generate a texture containing the message we want to display
	*  @param message The message we want to display
	*  @param fontFile The font we want to use to render the text
	*  @param color The color we want the text to be
	*  @param fontSize The size we want the font to be
	*  @return An SDL_Texture* to the rendered message
	*/
	static SDL_Texture* renderText(const char* message, const char* fontFile, SDL_Color color, int fontSize);
	static SDL_Texture* renderText(const string &message, const string &fontFile, SDL_Color color, int fontSize);

	static int drawLine(int x1, int y1, int x2, int y2);
	static int drawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	static int drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

	static void addSpriteState(Character* Character, int state, const char * filename, SDL_Color delimiterColor, bool stoppable);

	static Uint32 getPixel32(SDL_Surface *surface, int x, int y);
	static void putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);

	///Clear the renderer
	static void clear();
	///Present the renderer, ie. update screen
	static void present();
	///Get the window's box
	static SDL_Rect getBox();

private:
	static unique_ptr<SDL_Window, void (*)(SDL_Window*)> _window;
	static unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _renderer;
	static SDL_Rect mBox;
};

#endif