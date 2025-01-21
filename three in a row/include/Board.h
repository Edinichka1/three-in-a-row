#pragma once

#include "Stone.h"


class Board {
	
private:
	int board_width;
	int board_height;

	Stone*** board;

public:
	Board(int width, int height, int squareSize);
	~Board();

	int getBoardWidth();
	int getBoardHeight();

	Stone* getStone(int i, int j);
	void swapStones(int i1, int j1, int i2, int j2, int squareSize);
	bool check(int& x, int& y, StoneType& type);
	StoneType createNewStoneType();
};
