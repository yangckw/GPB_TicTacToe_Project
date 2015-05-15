/*************************************************************/
//							Game.h
/*************************************************************/
#pragma once;

#include "Globals.h"
#include "SDLClass.h"
#include "GameBoard.h"
#include "SDLAudio.h"

enum GameState {NullState, Init, SplashScreen, MainMenu, GameRunning, ExitGame};

#define TileRows 3
#define TileColums 3

struct Player
{
	int playerScore;
	bool isPlayer;
	bool isWinner;
	Player(int score, bool playerX, bool winner)
	{
		playerScore	= score;
		isPlayer	= playerX;
		isWinner	= winner;
	}
};

class Game
{
private:
	int round;
	GameState gameState;
	MySDL2 *sdl = new MySDL2;
	SDLAudio audio;
	GameBoard *board = new GameBoard;

	SDL_Texture* splashImage;
	SDL_Texture* logoImage;
	SDL_Texture* startButton;
	SDL_Texture* quitButton;
	SDL_Texture* gameBoard;
	SDL_Texture* xTile;
	SDL_Texture* oTile;
	Mix_Music *Loop120;
	Mix_Chunk *Blop;
public:
	Player *player1;
	Player *player2;
	Game();
	~Game();
	int mouseX;
	int mouseY;

	bool loadMedia(SDL_Texture*, string filename);
	void showSplashScreen();
	bool Initialize();
	void mainMenu();
	void runGame();
	void gameUpdate();
	void exitGame();
	void checkForWinner(int &stat);
	void renderBoard(SDL_Event);
	void mouseDownEvents(int);

	GameState returnState()			{ return gameState; }
	void setState(GameState state)	{ gameState = state; }
};