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
	int tempX = board[i1][j1]->getWindow_x();
	int tempY = board[i1][j1]->getWindow_y();

	board[i1][j1]->setStoneType(board[i2][j2]->getStoneType());
	board[i2][j2]->setStoneType(tempType);

	//board[i1][j1]->setWindow_x(board[i2][j2]->getWindow_x());
	//board[i1][j1]->setWindow_y(board[i2][j2]->getWindow_y());
	//board[i2][j2]->setWindow_x(tempX);
	//board[i2][j2]->setWindow_y(tempY);

	//Stone* mass[2];
	//mass[0] = board[i1][j1];
	//mass[1] = board[i2][j2];

	//int dx = squareSize / 20;
	//bool exitWhile = 0;
	//while (!exitWhile) {
	//	exitWhile = 1;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//	for (Stone* i : mass) {
	//		if (i->getWindow_y() == i->getBoard_y() * squareSize || i->getWindow_x() == i->getBoard_x() * squareSize) {

	//		}
	//		else if (i->getWindow_y() > i->getBoard_y() * squareSize || i->getWindow_y() > i->getBoard_y() * squareSize) {
	//			i->setWindow_y(i->getBoard_y() * squareSize);
	//		}
	//		else {
	//			i->setWindow_y(i->getWindow_y() + dx);
	//			exitWhile = 0;
	//		}
	//	}
	//}
}

bool Board::check(int& x, int& y, StoneType& type) {
	for (int i = 0; i < board_width - 2; ++i) {
		for (int j = 0; j < board_height; ++j) {
			if (board[i][j]->getStoneType() == board[i + 1][j]->getStoneType()
				&& board[i][j]->getStoneType() == board[i + 2][j]->getStoneType()) {
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
				&& board[i][j]->getStoneType() == board[i][j + 2]->getStoneType()) {
				x = i;
				y = j;
				type = board[i][j]->getStoneType();
				return 1;
			}
		}
	}

	return 0;
}