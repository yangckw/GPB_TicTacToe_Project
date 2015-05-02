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
	if (!sdl->loadMedia("TicTacToeLogo.png")) { cout << "Failed to load media!\n"; error = false; }

	// Input initalilize

	// Audio initalize

	return error;
}

void Game::mainMenu()
{

	sdl->renderClear();
	sdl->renderMenu();
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