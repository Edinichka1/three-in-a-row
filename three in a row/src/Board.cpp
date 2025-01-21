#include "Board.h"
#include <random>


Board::Board(int width, int height, int squareSize)
	:board_width(width), board_height(height) {

	std::srand(std::time(nullptr));

	board = new Stone * *[width];

	for (int i = 0; i < width; ++i) {
		board[i] = new Stone * [height];
		for (int j = 0; j < height; ++j) {
			StoneType type = createNewStoneType();
			board[i][j] = new Stone(squareSize * i, squareSize * j, i, j, 1.0, type);
		}
	}
	int x;
	int y;
	StoneType type;
	while (check(x, y, type)) {
		board[x][y]->setStoneType(createNewStoneType());
	}
}
Board::~Board() {
	for (int i = 0; i < board_width; ++i) {
		for (int j = 0; j < board_height; ++j) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}


StoneType Board::createNewStoneType() {
	return ((StoneType)(std::rand() % ((int)(StoneType::TYPES_LENGTH)-1)));
}

Stone* Board::getStone(int i, int j) {
	return board[i][j];
}

int Board::getBoardWidth() {
	return board_width;
}
int Board::getBoardHeight() {
	return board_height;
}

void Board::swapStones(int i1, int j1, int i2, int j2, int squareSize) {
	StoneType tempType = board[i1][j1]->getStoneType();
	int tempX1 = board[i1][j1]->getWindow_x();
	int tempY1 = board[i1][j1]->getWindow_y();
	int tempX2 = board[i2][j2]->getWindow_x();
	int tempY2 = board[i2][j2]->getWindow_y();

	Stone* stone1;
	Stone* stone2;
	double d = (squareSize / 20 > 0) ? (squareSize / 20) : 1;
	if (tempX1 - tempX2) {
		if (tempX2 - tempX1 > 0) {
			stone1 = board[i1][j1];
			stone2 = board[i2][j2];
		}
		else {
			stone1 = board[i2][j2];
			stone2 = board[i1][j1];

			std::swap(tempX1, tempX2);
		}
		bool exitWhile = 0;
		while (!exitWhile) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (stone1->getWindow_x() + d < tempX2) {
				stone1->setWindow_x(stone1->getWindow_x() + d);
				exitWhile = 0;
			}
			else {
				stone1->setWindow_x(tempX2);
				exitWhile = 1;
			}

			if (stone2->getWindow_x() - d > tempX1) {
				stone2->setWindow_x(stone2->getWindow_x() - d);
				exitWhile = 0;
			}
			else {
				stone2->setWindow_x(tempX1);
				exitWhile = 1;
			}
		}
		board[i1][j1]->setWindow_x(board[i1][j1]->getBoard_x() * squareSize);
		board[i2][j2]->setWindow_x(board[i2][j2]->getBoard_x() * squareSize);
	}
	else {
		if (tempY2 - tempY1 > 0) {
			stone1 = board[i1][j1];
			stone2 = board[i2][j2];
		}
		else {
			stone1 = board[i2][j2];
			stone2 = board[i1][j1];

			std::swap(tempY1, tempY2);
		}
		bool exitWhile = 0;
		while (!exitWhile) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (stone1->getWindow_y() + d < tempY2) {
				stone1->setWindow_y(stone1->getWindow_y() + d);
				exitWhile = 0;
			}
			else {
				stone1->setWindow_y(tempY2);
				exitWhile = 1;
			}

			if (stone2->getWindow_y() - d > tempY1) {
				stone2->setWindow_y(stone2->getWindow_y() - d);
				exitWhile = 0;
			}
			else {
				stone2->setWindow_y(tempY1);
				exitWhile = 1;
			}
		}
		board[i1][j1]->setWindow_y(board[i1][j1]->getBoard_y() * squareSize);
		board[i2][j2]->setWindow_y(board[i2][j2]->getBoard_y() * squareSize);
	}
	board[i1][j1]->setStoneType(board[i2][j2]->getStoneType());
	board[i2][j2]->setStoneType(tempType);
}

bool Board::check(int& x, int& y, StoneType& type) {
	for (int i = 0; i < board_width - 2; ++i) {
		for (int j = 0; j < board_height; ++j) {
			if (board[i][j]->getStoneType() == board[i + 1][j]->getStoneType()
				&& board[i][j]->getStoneType() == board[i + 2][j]->getStoneType() 
				&& board[i][j]->getStoneType() != StoneType::NONE) {
				x = i;
				y = j;
				type = board[i][j]->getStoneType();
				return 1;
			}
		}
	}
	for (int i = 0; i < board_width; ++i) {
		for (int j = 0; j < board_height - 2; ++j) {
			if (board[i][j]->getStoneType() == board[i][j + 1]->getStoneType()
				&& board[i][j]->getStoneType() == board[i][j + 2]->getStoneType()
				&&board[i][j]->getStoneType() != StoneType::NONE) {
				x = i;
				y = j;
				type = board[i][j]->getStoneType();
				return 1;
			}
		}
	}

	return 0;
}