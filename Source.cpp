/*************************************************************/
//					Tic Tac Toe Project
/*************************************************************/
#include "GameClass.h"

int main(int argc, char* args[])
{	
	Game *game = new Game();
	Player player1(0, true, false);
	Player player2(0, false, false);

	bool runEngine = true;
	bool isInitialized = false;
	SDL_Event e;

	game->setState(Init);

	while (runEngine)
	{
		switch (game->returnState())
		{
		case Init:
			isInitialized = game->Initialize();

			if (isInitialized)	{ game->setState(SplashScreen); }
			else				{ game->setState(ExitGame); }

			break;
		case SplashScreen:
			game->showSplashScreen();
			break;
		case MainMenu:
			game->mainMenu();
			break;
		case GameRunning:
			break;
		case ExitGame:
			runEngine = false;
			break;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) { game->setState(ExitGame); }
		}

		// Update mouse
		SDL_GetMouseState(&game->mouseX, &game->mouseY);
	}

	game->~Game();

	return 0;
}