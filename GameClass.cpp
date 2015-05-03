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
	sdl->loadMedia("Menu.png");
	SDL_Rect mainMenu_Rect;
	mainMenu_Rect.x = 0;
	mainMenu_Rect.y = 0;
	mainMenu_Rect.w = sdl->returnWidth();
	mainMenu_Rect.h = sdl->returnHeight();
	
	// Render the splash screen
	sdl->renderClear();
	sdl->render();
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
	sdl->loadMedia("TicTacToeLogo.png");
	SDL_Rect logoImage_Rect;
	logoImage_Rect.x = 0;
	logoImage_Rect.y = 0;
	logoImage_Rect.w = sdl->returnWidth();
	logoImage_Rect.h = sdl->returnHeight();

	// Render the splash screen
	sdl->renderClear();
	sdl->render();
	sdl->renderUpdate();

	// Pause the splash screen for 5 seconds
	SDL_Delay(5000);
	gameState = MainMenu;

}