#pragma once

#include "Board.h"


class Game {
	
private:
	int board_width;
	int board_height;
	int squareSize;
	Board* board;

	void clearStones(int x, int y, StoneType type);
	void animation();

public:
	Game();
	~Game();

	void start();

	void createNewGame(int width, int height, int squareSize);
	void loadGame();
	void saveGame();

	int getBoardWidth();
	int getBoardHeight();

	Stone* getStone(int i, int j);
	void swapStones(int i1, int j1, int i2, int j2);
};