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
Game::Game() : gameState(NullState), logoImage(NULL), startButton(NULL), 
				quitButton(NULL), mouseX(0), mouseY(0), splashImage(NULL), 
				gameBoard(NULL), xTile(NULL), oTile(NULL), Loop120(NULL),
				Blop(NULL), round(1)
{
}

bool Game::Initialize()
{
	bool error = true;

	sdl->setScreenSize(600, 800);			// Set Window size
	sdl->setWindowName("TicTacToe");		// Set the window name

	// SDL initialize
	if (!sdl->init())			{ cout << "Failed to initialize!\n"; error = false; }
	if (!audio.initAudio())		{ error = false; }
	
	// Load the background, X, O images
	gameBoard	= sdl->loadTexture("Images/Board.png");
	xTile		= sdl->loadTexture("Images/x.png");
	oTile		= sdl->loadTexture("Images/o.png");

	// Load SplashScreenIMage
	splashImage = sdl->loadTexture("Images/TicTacToeLogo.png");

	// Load MainMenu images
	logoImage = sdl->loadTexture("Images/Menu.png");
	startButton = sdl->loadTexture("Images/StartButton.png");
	quitButton = sdl->loadTexture("Images/QuitButton.png");

	// Load Audio files
	Blop = audio.loadWaveFiles(Blop, "Audio/Blop.wav");
	Loop120 = audio.loadMusicFiles(Loop120, "Audio/Loop_120_bpm.wav");

	return error;
}

void Game::mainMenu()
{
	SDL_Rect mainMenuRect = { 0, 0, 0, 0 };
	mainMenuRect = sdl->setRect(mainMenuRect, 0, 0, sdl->returnWidth(), sdl->returnHeight());
	
	SDL_Rect startButtonRect = { 0, 0, 0, 0 };
	startButtonRect = sdl->setRect(startButtonRect, sdl->returnWidth() / 2 - 50, sdl->returnHeight() / 2, 100, 40);

	SDL_Rect quitButtonRect = { 0, 0, 0, 0 };
	quitButtonRect = sdl->setRect(quitButtonRect, sdl->returnWidth() / 2 - 50, sdl->returnHeight() / 2 + 80, 100, 40);
	
	// Render the splash screen
	sdl->renderClear();
	sdl->myRenderCopy(logoImage, mainMenuRect);
	sdl->myRenderCopy(startButton, startButtonRect);
	sdl->myRenderCopy(quitButton, quitButtonRect);
	sdl->renderUpdate();

	SDL_Event e;
	SDL_PollEvent(&e);

	// Mouse checks for the buttons (Start)
	if (mouseX >= startButtonRect.x && mouseX <= startButtonRect.x + startButtonRect.w &&
		mouseY >= startButtonRect.y && mouseY <= startButtonRect.y + startButtonRect.h)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			gameState = GameRunning;
			audio.playWave(Blop);
		}
	}

	// Mouse checks for the buttons (Quit)
	if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.x + quitButtonRect.w &&
		mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.y + quitButtonRect.h)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{ 
			gameState = ExitGame;
			audio.playWave(Blop);
			audio.stopPlayingMusic();
		}
	}
}

void Game::runGame()
{
	// Create board rect
	SDL_Rect boardSide		= { 0, 0, 0, 0 };
	SDL_Rect scoreSide		= { 0, 0, 0, 0 };
	SDL_Rect boardSquares	= { 0, 0, 0, 0 };

	sdl->renderClear();			// Clear the screen
		
	// Setup the board (600 x 600)
	boardSide = sdl->setRect(boardSide, 0, 0, 600, 600);
	SDL_RenderSetViewport(sdl->returnRender(), &boardSide);

	// Set the square size for board
	boardSquares = sdl->setRect(boardSquares, 0, 0, 30, 30);
	board->setTexture(xTile, 0);

	// Array to setup the board all the same size
	board->setSquareSize(boardSquares, 10, 10);

	// Squares
	board->showSquare(sdl->returnRender(), 0);

	// Render Texture to screen
	SDL_RenderCopy(sdl->returnRender(), gameBoard, NULL, NULL);

	/***************************************************************/
	//						Score panel
	/***************************************************************/
	scoreSide = sdl->setRect(scoreSide, 600, 0, 200, 600);
	SDL_RenderSetViewport(sdl->returnRender(), &scoreSide);
	
	// Render Texture to screen
	SDL_RenderCopy(sdl->returnRender(), oTile, NULL, NULL);

	// Render everything
	sdl->renderUpdate();
}

void Game::exitGame()
{
	// Close extra memory usage
	SDL_DestroyTexture(logoImage);
	logoImage = NULL;

	SDL_DestroyTexture(startButton);
	startButton = NULL;

	SDL_DestroyTexture(quitButton);
	quitButton = NULL;

	//Free loaded image
	SDL_DestroyTexture(gameBoard);
	gameBoard = NULL;
	SDL_DestroyTexture(xTile);
	xTile = NULL;
	SDL_DestroyTexture(oTile);
	oTile = NULL;

	//Free the audio effects
	Mix_FreeChunk(Blop);
	Mix_FreeMusic(Loop120);
	Blop = NULL;
	Loop120 = NULL;
}

void Game::gameUpdate() { }

void Game::showSplashScreen()
{
	SDL_Rect logoImageRect = { 0, 0, 0, 0 };		// Initialize Rect

	audio.playMusic(Loop120);
	logoImageRect = sdl->setRect(logoImageRect, 0, 0, sdl->returnWidth(), sdl->returnHeight());

	sdl->renderClear();
	sdl->myRenderCopy(splashImage, logoImageRect);
	sdl->renderUpdate();

	// Pause the splash screen for 3 seconds *modified for faster testing
	SDL_Delay(3000);
	gameState = MainMenu;
}

void Game::checkForWinner()
{
	// check for winners
	if (board->checkForXWinner())	{ /* future home */ }
	if (board->CheckForOWinnder())	{ /*future home */ }
	if (round == 9 && !board->checkForXWinner() && !board->CheckForOWinnder())
	{
		// do something here
	}

	round++;
}