/*************************************************************/
//					Tic Tac Toe Project
/*************************************************************/
#include "GameClass.h"

int main(int argc, char* args[])
{	
	Game *game = new Game();

	bool runEngine = true;
	bool isInitialized = false;
	SDL_Event e;
	int variable = 0;

	game->setState(Init);

	while (runEngine)
	{
		switch (game->returnState())
		{
		case Init:
			if (game->Initialize())	{ game->setState(SplashScreen); }
			else					{ game->setState(ExitGame); }

			break;
		case SplashScreen:
			game->showSplashScreen();
			break;
		case MainMenu:
			game->mainMenu();
			break;
		case GameRunning:
			game->runGame();
			game->checkForWinner(variable);
			if (variable > 0) 
			{ 
				game->setState(MainMenu);
				game->resetViewArea();
			}
			break;
		case ExitGame:
			runEngine = false;
			break;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) { game->setState(ExitGame); }

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				for (int i = 0; i < 9; i++)
				{
					game->mouseDownEvents(i);
				}
			}
		}

		// Update mouse
		SDL_GetMouseState(&game->mouseX, &game->mouseY);
	}

	game->~Game();

	return 0;
}