/************************************************/
//						SDL 2
/************************************************/
#include <iostream>
#include <string>
#include <cmath>

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

using std::string;
using std::cout;

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

class MySDL2
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	SDL_Surface* gScreenSurface;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Texture* gTexture;
public:
	MySDL2();
	~MySDL2();

	bool init();
	bool loadMedia(string filename);
	SDL_Texture* loadTexture(string path);
	void renderClear();
	void render();
	void renderUpdate();
	void close();

	// Getters
	int returnWidth()							{ return SCREEN_WIDTH; }
	int returnHeight()							{ return SCREEN_HEIGHT; }
	SDL_Surface* returngScreenSurface()			{ return gScreenSurface; }
	SDL_Window* returngWindow()					{ return gWindow; }
};