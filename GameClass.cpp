#include "GameClass.h"

// Deconstructor
Game::~Game()
{
	sdl->~MySDL2();

	if (sdl)	{ delete sdl; sdl = NULL; }
}

// Overloaded constructor
Game::Game() : gameState(NullState) {}

bool Game::Initialize()
{
	bool error = true;

	// SDL initialize
	if (!sdl->init()) { cout << "Failed to initialize!\n"; error = false; }

	// Load images
	//if (!sdl->loadMedia("StartButton.png"))		{ cout << "Failed to load startButton.png!\n"; error = false; }
	//if (!sdl->loadMedia("QuitButton.png"))		{ cout << "Failed to load quitButton.png!\n"; error = false; }

	// Input initalilize

	// Audio initalize

	return error;
}

void Game::mainMenu()
{
	SDL_Texture* logoImage = sdl->loadTexture("Menu.png");
	SDL_Rect* mainMenuRect = new SDL_Rect;
	mainMenuRect->x = 0;
	mainMenuRect->y = 0;
	mainMenuRect->w = sdl->returnWidth();
	mainMenuRect->h = sdl->returnHeight();
	
	SDL_Texture* startButton = sdl->loadTexture("StartButton.png");
	SDL_Rect* startButtonRect = new SDL_Rect;
	startButtonRect->x = sdl->returnWidth() / 2 - 50;
	startButtonRect->y = sdl->returnHeight() / 2;
	startButtonRect->w = 100;
	startButtonRect->h = 40;

	SDL_Texture* quitButton = sdl->loadTexture("QuitButton.png");
	SDL_Rect* quitButtonRect = new SDL_Rect;
	quitButtonRect->x = sdl->returnWidth() / 2 - 50;
	quitButtonRect->y = sdl->returnHeight() / 2 + 80;	// Move button down by 80
	quitButtonRect->w = 100;
	quitButtonRect->h = 40;
	
	// Render the splash screen
	sdl->renderClear();
	sdl->myRenderCopy(logoImage, mainMenuRect);
	sdl->myRenderCopy(startButton, startButtonRect);
	sdl->myRenderCopy(quitButton, quitButtonRect);
	sdl->renderUpdate();
}

bool Game::runGame()
{
	return true;
}

void Game::exitGame()
{

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

	// Pause the splash screen for 5 seconds
	SDL_Delay(5000);
	gameState = MainMenu;

}