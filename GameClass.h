/*************************************************************/
//							Game.h
/*************************************************************/
#include "SDLClass.h"

enum GameState {NullState, Init, SplashScreen, MainMenu, GameRunning, ExitGame};

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
	SDL_Texture* logoImage;
	SDL_Rect* mainMenuRect;
	SDL_Texture* startButton;
	SDL_Rect* startButtonRect;
	SDL_Texture* quitButton;
	SDL_Rect* quitButtonRect;
public:
	Game();
	~Game();
	int mouseX;
	int mouseY;

	void showSplashScreen();
	bool Initialize();
	void mainMenu();
	bool runGame();
	void gameUpdate();
	void exitGame();

	GameState returnState()			{ return gameState; }
	void setState(GameState state)	{ gameState = state; }
};