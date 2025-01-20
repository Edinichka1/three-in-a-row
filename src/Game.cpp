#include "Game.h"
#include <thread>
#include <set>


Game::Game() {

}
Game::~Game() {
	delete board;
}

void Game::start() {

}

void Game::createNewGame(int width, int height, int squareSize) {
	this->squareSize = squareSize;
	board_width = width;
	board_height = height;
	board = new Board(board_width, board_height, squareSize);
}

void Game::loadGame() {

}

void Game::saveGame() {

}

int Game::getBoardWidth() { return board_width; }
int Game::getBoardHeight() { return board_height; }

Stone* Game::getStone(int i, int j) {
	return board->getStone(i, j);
}

void Game::clearStones(int x, int y, StoneType type) {
	if (x < board->getBoardWidth() && x >= 0 && y < board->getBoardHeight() && y >= 0) {
		Stone* stone = board->getStone(x, y);
		if (stone->getStoneType() == type) {
			stone->setStoneType(StoneType::NONE);
			clearStones(x + 1, y, type);
			clearStones(x, y + 1, type);
			clearStones(x - 1, y, type);
			clearStones(x, y - 1, type);
		}
	}
}

void Game::animation() {
	std::set<Stone*> set;

	for (int i = 0; i < board_width; ++i) {
		for (int j = board_height - 1; j >= 0 ; --j) {
			if (board->getStone(i, j)->getStoneType() == StoneType::NONE) {
				int noneCount = 0;
				for (int k = j; k >= 0; --k) {
					if (board->getStone(i, k)->getStoneType() == StoneType::NONE) {
						noneCount++;
					}
				}

				for (int k = 0; k < noneCount; ++k) {
					for (int h = j; h >= 0; --h) {
						Stone* stone = board->getStone(i, h);
						stone->setWindow_y(stone->getWindow_y() - squareSize);
						if (h - 1 >= 0) {
							stone->setStoneType(board->getStone(i, h - 1)->getStoneType());
						}
						else {
							stone->setStoneType(board->createNewStoneType());
						}
						set.insert(stone);
					}
				}
			}
		}
	}
	//board->getStone(0, 0)->setStoneType(StoneType::BLUE); вниз
	//board->getStone(0, 1)->setStoneType(StoneType::BLUE);

	for (Stone* i : set) {
		if (i->getStoneType() == StoneType::NONE) {
			i->setStoneType(board->createNewStoneType());
		}
	}

	double dx = squareSize / 20;

	bool exitWhile = 0;
	while (!exitWhile) {
		exitWhile = 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		for (Stone* i : set) {
			if (i->getWindow_y() == i->getBoard_y() * squareSize) {

			}
			else if (i->getWindow_y() > i->getBoard_y() * squareSize) {
				i->setWindow_y(i->getBoard_y() * squareSize);
			}
			else {
				i->setWindow_y(i->getWindow_y() + dx);
				exitWhile = 0;
			}
		}
	}
}

void Game::swapStones(int i1, int j1, int i2, int j2) {
	board->swapStones(i1, j1, i2, j2, squareSize);
	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	int x, y;
	StoneType type;
	bool temp = 0;

	while (board->check(x, y, type)) {
		clearStones(x, y, type);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		animation();
		temp = 1;
	}
	if(!temp) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		board->swapStones(i2, j2, i1, j1, squareSize);
		return;
	}
}