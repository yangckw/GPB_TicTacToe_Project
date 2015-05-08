/***********************************************************/
//					GameBoard.cpp
/***********************************************************/
#include "GameBoard.h"

GameBoard::GameBoard()
{
	resetBoard();
}

GameBoard::~GameBoard() {}

void GameBoard::resetBoard()
{
	// Initialize the boardSlots to Empty
	for (int i = 0; i < TileRows; i++)
	{
		for (int j = 0; j < TileColums; j++)
			boardSlots[i][j] = Empty;
	}
}