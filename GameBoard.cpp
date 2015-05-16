/***********************************************************/
//					GameBoard.cpp
/***********************************************************/
#include "GameBoard.h"

GameBoard::GameBoard()
{
	// Clear the board
	resetBoard();

	// initialize the Sqaures
	board[0].box = setRect(board[0].box, 25, 25, 150, 150);
	board[1].box = setRect(board[1].box, 225, 25, 150, 150);
	board[2].box = setRect(board[2].box, 425, 25, 150, 150);
	board[3].box = setRect(board[3].box, 25, 225, 150, 150);
	board[4].box = setRect(board[4].box, 225, 225, 150, 150);
	board[5].box = setRect(board[5].box, 425, 225, 150, 150);
	board[6].box = setRect(board[6].box, 25, 425, 150, 150);
	board[7].box = setRect(board[7].box, 225, 425, 150, 150);
	board[8].box = setRect(board[8].box, 425, 425, 150, 150);
}

GameBoard::~GameBoard() { closeGameBoard(); }

void GameBoard::resetBoard()
{
	// Initialize the boardSlots to Empty
	for (int i = 0; i < MaxSquares; i++)
	{
		board[i].state = Empty;
		board[i].tImage = NULL;
	}
}

bool GameBoard::checkSlotX(int num)
{
	bool taken = false;

	if (board[num].state == Xs) { taken = true; }
	
	return taken;
}

bool GameBoard::checkSlotO(int num)
{
	bool taken = false;

	if (board[num].state == Os)		{ taken = true; }

	return taken;
}

void GameBoard::setTexture(SDL_Texture* image, int num)
{
	board[num].tImage = image;
}

void GameBoard::setSquareState(Tiles tState, int num)
{
	board[num].state = tState;
}

void GameBoard::showSquare(SDL_Renderer* render, int num)
{
	board[num].box.x;
	board[num].box.y;
	board[num].box.w;
	board[num].box.h;
	SDL_RenderCopy(render, board[num].tImage, NULL, &board[num].box);
}

void GameBoard::closeGameBoard()
{
	if (board) { delete[] board; }
}

bool GameBoard::checkForXWinner()
{
	bool isWinner = false;

	// Check for X's wins
	if (board[0].state == Xs && board[1].state == Xs && board[2].state == Xs ||
		board[3].state == Xs && board[4].state == Xs && board[5].state == Xs ||
		board[6].state == Xs && board[7].state == Xs && board[8].state == Xs ||
		board[0].state == Xs && board[4].state == Xs && board[8].state == Xs ||
		board[2].state == Xs && board[4].state == Xs && board[6].state == Xs ||
		board[0].state == Xs && board[3].state == Xs && board[6].state == Xs ||
		board[1].state == Xs && board[4].state == Xs && board[7].state == Xs ||
		board[2].state == Xs && board[5].state == Xs && board[8].state == Xs)
	{
		isWinner = true;
	}
	return isWinner;
}

bool GameBoard::CheckForOWinner()
{
	bool isWinner = false;

	// Check for Y's wins
	if (board[0].state == Os && board[1].state == Os && board[2].state == Os ||
		board[3].state == Os && board[4].state == Os && board[5].state == Os ||
		board[6].state == Os && board[7].state == Os && board[8].state == Os ||
		board[0].state == Os && board[4].state == Os && board[8].state == Os ||
		board[2].state == Os && board[4].state == Os && board[6].state == Os ||
		board[0].state == Os && board[3].state == Os && board[6].state == Os ||
		board[1].state == Os && board[4].state == Os && board[7].state == Os ||
		board[2].state == Os && board[5].state == Os && board[8].state == Os)
	{
		isWinner = true;
	}

	return isWinner;
}

SDL_Rect GameBoard::setRect(SDL_Rect rect, int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;

	return rect;
}

bool GameBoard::checkForClick(int num, int mouseX, int mouseY)
{
	bool click = false;

	// Mouse checks for the buttons (Start)
	if (mouseX >= board[num].box.x && mouseX <= board[num].box.x + board[num].box.w &&
		mouseY >= board[num].box.y && mouseY <= board[num].box.y + board[num].box.h)
	{
		if (board[num].state == Empty)		{ click = true; }
	}

	return click;
}