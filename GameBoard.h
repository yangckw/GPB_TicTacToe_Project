/***********************************************************/
//						GameBoard.h
/***********************************************************/
#pragma once;

#include "Globals.h"

enum Tiles {Empty, Xs, Os};
#define MaxSquares 9

struct Squares
{
	SDL_Rect box;
	SDL_Texture* tImage;
	Tiles state;
};

class GameBoard
{
private:
	Squares board[MaxSquares];		// Hold an Array of Rect
public:
	GameBoard();
	~GameBoard();
	void resetBoard();
	bool checkSlotX(int);
	bool checkSlotO(int);
	void setTexture(SDL_Texture*, int);
	void setSquareState(Tiles, int);
	void showSquare(SDL_Renderer*, int);
	void closeGameBoard();
	bool checkForXWinner();
	bool CheckForOWinner();
	bool checkForClick(int, int, int);
	SDL_Rect setRect(SDL_Rect, int, int, int, int);

	Tiles returnBoxState(int num)		{ return board[num].state; }
};