#include "SDLClass.h"

MySDL2::MySDL2() : gScreenSurface(NULL), gRenderer(NULL),
					SCREEN_HEIGHT(480), SCREEN_WIDTH(640), gWindow(NULL), gTexture(NULL) {}

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
		gWindow = SDL_CreateWindow("SDL tutorial 7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

bool MySDL2::loadMedia(string path)
{
	bool success = true;

	gTexture = loadTexture(path);
	if (gTexture == NULL)
	{
		cout << "Failed to load texture image!\n";
		success = false;
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
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

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

void MySDL2::render()
{
	//Top left corner viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 2;
	topLeftViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &topLeftViewport);

	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


	//Top right viewport
	SDL_Rect topRightViewport;
	topRightViewport.x = SCREEN_WIDTH / 2;
	topRightViewport.y = 0;
	topRightViewport.w = SCREEN_WIDTH / 2;
	topRightViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &topRightViewport);

	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);


	//Bottom viewport
	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport(gRenderer, &bottomViewport);


	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
}

void MySDL2::renderUpdate() { SDL_RenderPresent(gRenderer); }