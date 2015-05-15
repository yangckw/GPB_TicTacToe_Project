#include "SDLClass.h"

MySDL2::MySDL2() : gScreenSurface(NULL), gRenderer(NULL), SCREEN_HEIGHT(600), 
					SCREEN_WIDTH(800), gWindow(NULL), windowName("") {}

MySDL2::~MySDL2() { close(); }

bool MySDL2::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		// Create window
		gWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		else 
		{ 
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError();
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_Image could not be initialized! SDL_Error: " << IMG_GetError() << "\n";
					success = false;
				}
			}			
		}
	}
	return success;
}

SDL_Texture* MySDL2::loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		cout << "Unable to load image, SDL Error: " << path.c_str() << ", " << SDL_GetError();
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			cout << "Unable to optimize image SDL Error: " << path.c_str() << ", " << SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void MySDL2::close()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow		= NULL;
	gRenderer	= NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void MySDL2::renderClear() { SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); SDL_RenderClear(gRenderer); }

void MySDL2::render() { SDL_RenderPresent(gRenderer); }

void MySDL2::renderUpdate() { SDL_RenderPresent(gRenderer); }

void MySDL2::myRenderCopy(SDL_Texture* texture, SDL_Rect myRect)
{
	SDL_RenderCopy(gRenderer, texture, NULL, &myRect);
}

SDL_Rect MySDL2::setRect(SDL_Rect rect, int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;

	return rect;
}

void MySDL2::setScreenSize(int height, int width)
{
	SCREEN_HEIGHT = height;
	SCREEN_WIDTH = width;
}