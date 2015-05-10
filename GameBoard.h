/***********************************************************/
//						GameBoard.h
/***********************************************************/
#pragma once;

#include "Globals.h"

enum Tiles {Empty, Xs, Os};
#define MaxSquares 9

struct Squares
{
	SDL_Rect squares;
	SDL_Texture* tImage;
	Tiles state;
};

class GameBoard
{
private:
	Squares squares[MaxSquares];		// Hold an Array of Rects	
public:
	GameBoard();
	~GameBoard();
	void resetBoard();
	bool checkSlot(int);
	void displayBoard();
	void setSquareSize(SDL_Rect, int, int);
	void setTexture(SDL_Texture*, int);
	void setSquareState(Tiles, int);
	void showSquare(SDL_Renderer*, int);
	void closeGameBoard();
	bool checkForXWinner();
	bool CheckForOWinnder();
};