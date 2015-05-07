#include "GameClass.h"

// Deconstructor
Game::~Game()
{
	// Close out Game Class
	exitGame();

	// Shutdown SDL2 Class
	sdl->~MySDL2();
	if (sdl)	{ delete sdl; sdl = NULL; }
}

// Overloaded constructor
Game::Game() : gameState(NullState), logoImage(NULL), mainMenuRect(NULL), startButtonRect(NULL),
				startButton(NULL), quitButton(NULL), quitButtonRect(NULL), mouseX(0), mouseY(0)
{
	mainMenuRect		= new SDL_Rect;
	startButtonRect		= new SDL_Rect;
	quitButtonRect		= new SDL_Rect;
}


	//The music that will be played
	Mix_Music *gLoop = NULL;

	//The sound effects that will be used
	Mix_Chunk *gBlop = NULL;
	Mix_Chunk *gWoosh = NULL;


bool Game::Initialize()
{
	bool error = true;

	// SDL initialize
	if (!sdl->init()) { cout << "Failed to initialize!\n"; error = false; }

	// Load images
	//if (!sdl->loadMedia("StartButton.png"))		{ cout << "Failed to load startButton.png!\n"; error = false; }
	//if (!sdl->loadMedia("QuitButton.png"))		{ cout << "Failed to load quitButton.png!\n"; error = false; }

	// Input initalilize


	// Audio initalilize
//	if (!sdl->loadMedia()) { cout << "Failed to initialize!\n"; error = false; }



	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		error = false;	}

	return error;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool error = true;

	//Load music
	gLoop = Mix_LoadMUS("Audio/Loop_120_bpm.wav");
	if (gLoop == NULL)
	{	printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		error = false;	}

	//Load sound effects
	gBlop = Mix_LoadWAV("Audio/Blop.wav");
	if (gBlop == NULL)
	{	printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		error = false;	}

	gWoosh = Mix_LoadWAV("Audio/Woosh.wav");
	if (gWoosh == NULL)
	{	printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		error = false;	}

	return error;
	
}

void Game::mainMenu()
{
	logoImage = sdl->loadTexture("Menu.png");	
	mainMenuRect->x = 0;
	mainMenuRect->y = 0;
	mainMenuRect->w = sdl->returnWidth();
	mainMenuRect->h = sdl->returnHeight();
	
	startButton = sdl->loadTexture("StartButton.png");	
	startButtonRect->x = sdl->returnWidth() / 2 - 50;
	startButtonRect->y = sdl->returnHeight() / 2;
	startButtonRect->w = 100;
	startButtonRect->h = 40;

	quitButton = sdl->loadTexture("QuitButton.png");
	quitButtonRect->x = sdl->returnWidth() / 2 - 50;
	quitButtonRect->y = sdl->returnHeight() / 2 + 80;	// Move button down by 80
	quitButtonRect->w = 100;
	quitButtonRect->h = 40;

	// Play file
//	Mix_PlayMusic( gLoop, -1);
//	Mix_PlayChannel(-1, gBlop, 0);
	
	// Render the splash screen
	sdl->renderClear();
	sdl->myRenderCopy(logoImage, mainMenuRect);
	sdl->myRenderCopy(startButton, startButtonRect);
	sdl->myRenderCopy(quitButton, quitButtonRect);
	sdl->renderUpdate();

	SDL_Event e;
	SDL_PollEvent(&e);

	// Mouse checks for the buttons (Start)
	if (mouseX >= startButtonRect->x && mouseX <= startButtonRect->x + startButtonRect->w &&
		mouseY >= startButtonRect->y && mouseY <= startButtonRect->y + startButtonRect->h)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) { gameState = GameRunning; }
	}

	// Mouse checks for the buttons (Quit)
	if (mouseX >= quitButtonRect->x && mouseX <= quitButtonRect->x + quitButtonRect->w &&
		mouseY >= quitButtonRect->y && mouseY <= quitButtonRect->y + quitButtonRect->h)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) { gameState = ExitGame; }
	}
}

bool Game::runGame()
{
	return true;
}

void Game::exitGame()
{	
	//Free the audio effects
	Mix_FreeChunk(gBlop);
	Mix_FreeChunk(gWoosh);
	Mix_FreeMusic(gLoop);
	gBlop = NULL;
	gWoosh = NULL;
	gLoop = NULL;

	// Close extra memory usage
	SDL_DestroyTexture(logoImage);
	logoImage = NULL;
	if (mainMenuRect)		{ delete mainMenuRect; }

	if (startButtonRect)	{ delete startButtonRect; }
	SDL_DestroyTexture(startButton);
	startButton = NULL;

	if (quitButtonRect)		{ delete quitButtonRect; }
	SDL_DestroyTexture(quitButton);
	quitButton = NULL;
	
}

void Game::gameUpdate()
{
	
}

void Game::showSplashScreen()
{
	SDL_Texture* splashImage = sdl->loadTexture("TicTacToeLogo.png");
	if (splashImage == NULL) { cout << "Error Loading Splash Image!!\n"; }
	SDL_Rect* logoImageRect = new SDL_Rect;
	
	logoImageRect->x = 0;
	logoImageRect->y = 0;
	logoImageRect->w = sdl->returnWidth();
	logoImageRect->h = sdl->returnHeight();	


	sdl->renderClear();
	sdl->myRenderCopy(splashImage, logoImageRect);
	sdl->renderUpdate();

	// Pause the splash screen for 3 seconds *modified for faster testing
	SDL_Delay(3000);
	gameState = MainMenu;
}