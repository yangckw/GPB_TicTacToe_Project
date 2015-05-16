/************************************************/
//						SDL 2
/************************************************/
#pragma once;

#include "Globals.h"

class MySDL2
{
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	char *windowName;

	SDL_Surface* gScreenSurface;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
public:
	MySDL2();
	~MySDL2();

	bool init();
	bool loadAudio();
	SDL_Texture* loadTexture(string path);
	void renderClear();
	void render();
	void myRenderCopy(SDL_Texture* texture, SDL_Rect rect);
	void close();
	void renderBoard();
	SDL_Rect setRect(int, int, int, int);
	void setScreenSize(int, int);

	void renderText( 
					SDL_Rect quad,
					SDL_Texture* texture,
					SDL_Rect* clip = NULL,
					double angle = 0.0, 
					SDL_Point* center = NULL, 
					SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Getters
	int returnWidth()							{ return SCREEN_WIDTH; }
	int returnHeight()							{ return SCREEN_HEIGHT; }
	SDL_Surface* returngScreenSurface()			{ return gScreenSurface; }
	SDL_Window* returngWindow()					{ return gWindow; }
	SDL_Renderer* returnRender()				{ return gRenderer; }

	// Setters
	void setWindowName(char *name)				{ windowName = name; }
};