#pragma once
#include <mutex>


enum class StoneType {
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	NONE,
	TYPES_LENGTH
};


class Stone {

private:
	std::mutex mutex;
	int board_x;
	int board_y;
	double window_x;
	double window_y;
	double size;
	StoneType stoneType;

public:
	Stone(double window_x, double window_y, int board_x, int board_y, double size, StoneType stoneType);

	double getWindow_x();
	double getWindow_y();
	int getBoard_x();
	int getBoard_y();
	void setWindow_x(double newX);
	void setWindow_y(double newY);
	void setBoard_x(int newX);
	void setBoard_y(int newY);
	double getSize();
	void setSize(double newSize);
	StoneType getStoneType();
	void setStoneType(StoneType type);
};