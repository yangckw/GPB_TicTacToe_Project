/************************************************/
//						SDL 2
/************************************************/
#include <iostream>
#include <string>
#include <cmath>

#if _WIN32
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>	// Need to download, place directly into folder for instructor?
#else
#include <SDL2\SDL.h>
#include <SDL\SDL_image.h>	// Wait, why are the slashes facing the same way as the ones for _WIN32 above?
#include <SDL\SDL_mixer.h>
#endif

using std::string;
using std::cout;

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")

class MySDL2
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	SDL_Surface* gScreenSurface;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Texture* gTexture;
	SDL_Texture* gameBoard;
	SDL_Texture* xTile;
	SDL_Texture* oTile;
	Mix_Music *gLoop120;
	Mix_Chunk *gBlop;
	Mix_Chunk *gWoosh;
public:
	MySDL2();
	~MySDL2();

	bool init();
	bool loadMedia(string filename);
	bool loadAudio();
	SDL_Texture* loadTexture(string path);
	void renderClear();
	void render();
	void myRenderCopy(SDL_Texture* texture, SDL_Rect* rect);
	void renderUpdate();
	void close();
	void playLoop120();
	void playerBlop();
	void renderBoard();

	// Getters
	int returnWidth()							{ return SCREEN_WIDTH; }
	int returnHeight()							{ return SCREEN_HEIGHT; }
	SDL_Surface* returngScreenSurface()			{ return gScreenSurface; }
	SDL_Window* returngWindow()					{ return gWindow; }
	SDL_Renderer* returnRender()				{ return gRenderer; }
};