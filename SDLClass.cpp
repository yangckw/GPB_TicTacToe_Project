#include "SDLClass.h"

MySDL2::MySDL2() : gScreenSurface(NULL), gRenderer(NULL),
					SCREEN_HEIGHT(480), SCREEN_WIDTH(640), gWindow(NULL), gTexture(NULL),
					gLoop120(NULL), gBlop(NULL), gWoosh(NULL) {}

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

	// Audio initalilize
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: \n", Mix_GetError();
		success = false;
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

bool MySDL2::loadAudio()
{
	bool error = true;

	//Load music
	gLoop120 = Mix_LoadMUS("Audio/Loop_120_bpm.wav");

	if (gLoop120 == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << "\n";
		error = false;
	}

	//Load sound effects
	gBlop = Mix_LoadWAV("Audio/Blop.wav");

	if (gBlop == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		error = false;
	}

	gWoosh = Mix_LoadWAV("Audio/Woosh.wav");
	if (gWoosh == NULL)
	{
		cout << "Failed to load high sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
		error = false;
	}
	return error;
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

	//Free the audio effects
	Mix_FreeChunk(gBlop);
	Mix_FreeChunk(gWoosh);
	Mix_FreeMusic(gLoop120);
	gBlop		= NULL;
	gWoosh		= NULL;
	gLoop120	= NULL;
}

void MySDL2::renderClear() { SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); SDL_RenderClear(gRenderer); }

void MySDL2::render() { SDL_RenderPresent(gRenderer); }

void MySDL2::renderUpdate() { SDL_RenderPresent(gRenderer); }

void MySDL2::myRenderCopy(SDL_Texture* texture, SDL_Rect* myRect)
{
	SDL_RenderCopy(gRenderer, texture, NULL, myRect);
}

void MySDL2::playLoop120()
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(gLoop120, -1);
		//Mix_PlayChannel(-1, gWoosh, 0);
}

void MySDL2::playerBlop()
{
	Mix_PlayChannel(-1, gBlop, 0);
}