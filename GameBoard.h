/***********************************************************/
//						GameBoard.h
/***********************************************************/

#define TileRows 3
#define TileColums 3

enum Tiles {Empty, X, O};

class GameBoard
{
private:
	int boardSlots[TileRows][TileColums];
public:
	GameBoard();
	~GameBoard();

	void resetBoard();
};