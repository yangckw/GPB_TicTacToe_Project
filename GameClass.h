/*************************************************************/
//							Game.h
/*************************************************************/
#include "SDLClass.h"

enum GameState {NullState, Init, MainMenu, GameRunning, ExitGame};

struct Player
{
	int playerScore;
	bool isPlayerX;
	bool isWinner;
	Player(int score, bool playerX, bool winner)
	{
		playerScore	= score;
		isPlayerX	= playerX;
		isWinner	= winner;
	}
};

class Game
{
private:
	GameState gameState;
	MySDL2 *sdl = new MySDL2;
public:
	Game();
	~Game();
	bool Initialize();
	void mainMenu();
	bool runGame();
	void gameUpdate();
	void exitGame();

	GameState returnState()			{ return gameState; }
	void setState(GameState state)	{ gameState = state; }
};