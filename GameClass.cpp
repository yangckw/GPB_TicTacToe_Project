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
				Blop(NULL), round(1), savoye(NULL)
{
	player1 = new Player(0, true, false);
	player2 = new Player(0, false, false);
}

bool Game::Initialize()
{
	bool success = true;

	sdl->setScreenSize(600, 800);			// Set Window size
	sdl->setWindowName("Tic Tac Toe");		// Set the window name

	// SDL initialize
	if (!sdl->init())			{ cout << "Failed to initialize!\n"; success = false; }
	if (!audio.initAudio())		{ success = false; }
	if (!sdltext.initText())	{ success = false; }
	
	// Load all Images & audio
	gameBoard		= sdl->loadTexture("Images/Board.png");
	xTile			= sdl->loadTexture("Images/x.png");
	oTile			= sdl->loadTexture("Images/o.png");
	splashImage		= sdl->loadTexture("Images/TicTacToeLogo.png");
	logoImage		= sdl->loadTexture("Images/Menu.png");
	startButton		= sdl->loadTexture("Images/StartButton.png");
	quitButton		= sdl->loadTexture("Images/QuitButton.png");
	Blop			= audio.loadWaveFiles(Blop, "Audio/Blop.wav");
	Loop120			= audio.loadMusicFiles(Loop120, "Audio/Loop_120_bpm.wav");
	savoye			= TTF_OpenFont("Fonts/Savoye_LET_Plain1.0.ttf", 12);

	// Checks for all loaded items.
	if (gameBoard	== NULL)	{ cout << "Could not load gameBoard "		<< SDL_GetError() << "\n"; success = false; }
	if (xTile		== NULL)	{ cout << "Could not load xTile "			<< SDL_GetError() << "\n"; success = false; }
	if (oTile		== NULL)	{ cout << "Could not load oTile "			<< SDL_GetError() << "\n"; success = false; }
	if (splashImage == NULL)	{ cout << "Could not load splashImage "		<< SDL_GetError() << "\n"; success = false; }
	if (logoImage	== NULL)	{ cout << "Could not load logoImage "		<< SDL_GetError() << "\n"; success = false; }
	if (startButton	== NULL)	{ cout << "Could not load startButton "		<< SDL_GetError() << "\n"; success = false; }
	if (quitButton	== NULL)	{ cout << "Could not load quitButton "		<< SDL_GetError() << "\n"; success = false; }
	if (Blop		== NULL)	{ cout << "Could not load Blop Audio "		<< SDL_GetError() << "\n"; success = false; }
	if (Loop120		== NULL)	{ cout << "Could not load Loop120 Audio "	<< SDL_GetError() << "\n"; success = false; }	
	if (savoye		== NULL)	{ cout << "Could not load savoye font "		<< SDL_GetError() << "\n"; success = false; }

	return success;
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
	sdl->render();

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
	Text gameTitle;		// Initialize text for Game title

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

	/***************************************************************/
	// Show score and game name
	/***************************************************************/
	/*gameTitle = sdltext.setFontColor(0, 0, 0);		// Sets text color
	gameTitle = sdltext.setFontPosition(20, 20);
	gameTitle = sdltext.renderToTexture(sdl->returnRender(), savoye, "Tic Tac Toe");
	sdl->renderText(gameTitle.box, gameTitle.texture);*/

	// Render everything
	sdl->render();
}

void Game::exitGame()
{
	// Clear in reverse order
	if (savoye		!= NULL)	{ TTF_CloseFont(savoye);			savoye		= NULL; }
	if (Loop120		!= NULL)	{ Mix_FreeMusic(Loop120);			Loop120		= NULL; }
	if (Blop		!= NULL)	{ Mix_FreeChunk(Blop);				Blop		= NULL; }
	if (quitButton	!= NULL)	{ SDL_DestroyTexture(quitButton);	quitButton	= NULL; }
	if (startButton != NULL)	{ SDL_DestroyTexture(startButton);	startButton = NULL; }
	if (logoImage	!= NULL)	{ SDL_DestroyTexture(logoImage);	logoImage	= NULL; }
	if (splashImage	!= NULL)	{ SDL_DestroyTexture(splashImage);	splashImage	= NULL; }
	if (oTile		!= NULL)	{ SDL_DestroyTexture(oTile);		oTile		= NULL; }
	if (xTile		!= NULL)	{ SDL_DestroyTexture(xTile);		xTile		= NULL; }
	if (gameBoard	!= NULL)	{ SDL_DestroyTexture(gameBoard);	gameBoard	= NULL; }

	// Clean up player class
	if (player1) { delete player1; }
	if (player2) { delete player2; }

	TTF_Quit();
}

void Game::showSplashScreen()
{
	SDL_Rect logoImageRect = { 0, 0, 0, 0 };		// Initialize Rect

	audio.playMusic(Loop120);						// Play Loop120 audio (Music)
	logoImageRect = sdl->setRect(0, 0, sdl->returnWidth(), sdl->returnHeight());

	sdl->renderClear();
	sdl->myRenderCopy(splashImage, logoImageRect);
	sdl->render();

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