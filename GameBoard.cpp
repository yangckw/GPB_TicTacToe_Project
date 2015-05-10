/***********************************************************/
//					GameBoard.cpp
/***********************************************************/
#include "GameBoard.h"

GameBoard::GameBoard()
{
	resetBoard();
}

GameBoard::~GameBoard() { closeGameBoard(); }

void GameBoard::resetBoard()
{
	// Initialize the boardSlots to Empty
	for (int i = 0; i < MaxSquares; i++)
	{
		squares[i].state = Empty;
		squares[i].tImage = NULL;
	}
}

bool GameBoard::checkSlot(int num)
{
	bool taken = false;

	if (squares[num].state == Xs || squares[num].state == Os) { taken = true; }
	
	return taken;
}

void GameBoard::setSquareSize(SDL_Rect rect, int padWidth, int padHeight)
{
	for (int i = 0; i < 9; i++)
	{
		squares[i].squares.x = rect.x;
		squares[i].squares.y = rect.y;
		squares[i].squares.w = rect.w + padWidth;
		squares[i].squares.h = rect.h + padHeight;
	}
}

void GameBoard::setTexture(SDL_Texture* image, int num)
{
	squares[num].tImage = image;
}

void GameBoard::setSquareState(Tiles tState, int num)
{
	squares[num].state = tState;
}

void GameBoard::showSquare(SDL_Renderer* render, int num)
{
	squares[num].squares.x;
	squares[num].squares.y;
	squares[num].squares.w;
	squares[num].squares.h;
	SDL_RenderCopy(render, squares[num].tImage, NULL, NULL);
}

void GameBoard::closeGameBoard()
{
	if (squares) { delete [] squares; }
}

bool GameBoard::checkForXWinner()
{
	bool isWinner = false;

	// Check for X's wins
	if (squares[0].state == Xs && squares[1].state == Xs && squares[2].state == Xs ||
		squares[3].state == Xs && squares[4].state == Xs && squares[5].state == Xs ||
		squares[6].state == Xs && squares[7].state == Xs && squares[8].state == Xs ||
		squares[0].state == Xs && squares[4].state == Xs && squares[8].state == Xs ||
		squares[2].state == Xs && squares[4].state == Xs && squares[6].state == Xs ||
		squares[0].state == Xs && squares[3].state == Xs && squares[6].state == Xs ||
		squares[1].state == Xs && squares[4].state == Xs && squares[7].state == Xs ||
		squares[2].state == Xs && squares[5].state == Xs && squares[8].state == Xs)
	{
		isWinner = true;
	}
	return isWinner;
}

bool GameBoard::CheckForOWinnder()
{
	bool isWinner = false;

	// Check for Y's wins
	if (squares[0].state == Os && squares[1].state == Os && squares[2].state == Os ||
		squares[3].state == Os && squares[4].state == Os && squares[5].state == Os ||
		squares[6].state == Os && squares[7].state == Os && squares[8].state == Os ||
		squares[0].state == Os && squares[4].state == Os && squares[8].state == Os ||
		squares[2].state == Os && squares[4].state == Os && squares[6].state == Os ||
		squares[0].state == Os && squares[3].state == Os && squares[6].state == Os ||
		squares[1].state == Os && squares[4].state == Os && squares[7].state == Os ||
		squares[2].state == Os && squares[5].state == Os && squares[8].state == Os)
	{
		isWinner = true;
	}
	return isWinner;
}