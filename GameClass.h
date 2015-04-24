/*************************************************************/
//							Game.h
/*************************************************************/
#include "SDLClass.h"

enum GameState {NullState, Init, MainMenu, GameRunning, ExitGame};

class Game
{
private:
	GameState gameState;
	MySDL2 *sdl = new MySDL2;
	int playerOneScore;
	int playerTwoScore;
public:
	Game();
	~Game();
	bool Initialize();
	void mainMenu();
	void runGame();
	void gameUpdate();
	void exitGame();
};