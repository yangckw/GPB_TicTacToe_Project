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
	player1 = new Player(0, true, false);
	player2 = new Player(0, false, false);
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
	mainMenuRect = sdl->setRect(0, 0, sdl->returnWidth(), sdl->returnHeight());
	
	SDL_Rect startButtonRect = { 0, 0, 0, 0 };
	startButtonRect = sdl->setRect(sdl->returnWidth() / 2 - 50, sdl->returnHeight() / 2, 100, 40);

	SDL_Rect quitButtonRect = { 0, 0, 0, 0 };
	quitButtonRect = sdl->setRect(sdl->returnWidth() / 2 - 50, sdl->returnHeight() / 2 + 80, 100, 40);
	
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

	sdl->renderClear();			// Clear the screen
		
	boardSide = sdl->setRect(0, 0, 600, 600);
	SDL_RenderSetViewport(sdl->returnRender(), &boardSide);

	// Render Texture to screen
	SDL_RenderCopy(sdl->returnRender(), gameBoard, NULL, NULL);

	for (int i = 0; i < 9; i++)
	{
		// Render the board
		board->showSquare(sdl->returnRender(), i);
	}

	/***************************************************************/
	//						Score panel
	/***************************************************************/
	scoreSide = sdl->setRect(600, 0, 200, 600);
	SDL_RenderSetViewport(sdl->returnRender(), &scoreSide);
	
	// Render Texture to screen
	SDL_RenderCopy(sdl->returnRender(), NULL, NULL, NULL);

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

	// Clean up player class
	if (player1) { delete player1; }
	if (player2) { delete player2; }
}

void Game::gameUpdate() { }

void Game::showSplashScreen()
{
	SDL_Rect logoImageRect = { 0, 0, 0, 0 };		// Initialize Rect

	audio.playMusic(Loop120);
	logoImageRect = sdl->setRect(0, 0, sdl->returnWidth(), sdl->returnHeight());

	sdl->renderClear();
	sdl->myRenderCopy(splashImage, logoImageRect);
	sdl->renderUpdate();

	// Pause the splash screen for 3 seconds *modified for faster testing
	SDL_Delay(3000);
	gameState = MainMenu;
}

void Game::checkForWinner(int &stat)
{
	// Check for X winner
	if (board->checkForXWinner())	{ stat = 1; }

	// Check for O winner
	if (board->CheckForOWinner())	{ stat = 2; }

	// Check for tie
	if (round == 10 && !board->checkForXWinner() && !board->CheckForOWinner())
	{
		stat = 3;
	}
}

void Game::mouseDownEvents(int num)
{
	bool downEvent = board->checkForClick(num, mouseX, mouseY);

	if (downEvent && board->returnBoxState(num) == Empty && player1->isPlayer == true)
	{
		board->setTexture(xTile, num);		// Set the Tile Texture
		board->setSquareState(Xs, num);		// Set Tile state (Xs)
		player1->playerScore += 100;		// Set player score to base plus 100

		// Swap players
		player1->isPlayer = false;
		player2->isPlayer = true;
		round++;
	}

	else if (downEvent && board->returnBoxState(num) == Empty && player2->isPlayer == true)
	{
		board->setTexture(oTile, num);		// Set the Tile texture
		board->setSquareState(Os, num);		// Set time state (Os)
		player2->playerScore += 100;		// Set player score to base plus 100

		// Swap players
		player1->isPlayer = true;
		player2->isPlayer = false;
		round++;
	}
}

void Game::resetViewArea()
{
	SDL_Rect empty;
	empty = sdl->setRect(0, 0, 800, 600);
	SDL_RenderSetViewport(sdl->returnRender(), NULL);
}