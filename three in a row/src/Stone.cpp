#include "Stone.h"


Stone::Stone(double window_x, double window_y, int board_x, int board_y, double size, StoneType stoneType)
	:window_x(window_x), window_y(window_y), board_x(board_x), board_y(board_y), size(size), stoneType(stoneType) {
}
double Stone::getWindow_x() { 
	std::lock_guard<std::mutex> lock(mutex); 
	return window_x; 
}
double Stone::getWindow_y() { 
	std::lock_guard<std::mutex> lock(mutex); 
	return window_y; 
}
int Stone::getBoard_x() { 
	std::lock_guard<std::mutex> lock(mutex); 
	return board_x;
}
int Stone::getBoard_y() { 
	std::lock_guard<std::mutex> lock(mutex); 
	return board_y; 
}
void Stone::setWindow_x(double newX) { 
	std::lock_guard<std::mutex> lock(mutex);
	window_x = newX; 
}
void Stone::setWindow_y(double newY) { 
	std::lock_guard<std::mutex> lock(mutex);
	window_y = newY; 
}
void Stone::setBoard_x(int newX) { 
	std::lock_guard<std::mutex> lock(mutex);
	board_x = newX;
}
void Stone::setBoard_y(int newY) { 
	std::lock_guard<std::mutex> lock(mutex);
	board_y = newY; 
}
double Stone::getSize() {
	std::lock_guard<std::mutex> lock(mutex);
	return size; 
}
void Stone::setSize(double newSize) {
	std::lock_guard<std::mutex> lock(mutex); 
	size = newSize; 
}
StoneType Stone::getStoneType() {
	std::lock_guard<std::mutex> lock(mutex);
	return stoneType; 
}
void Stone::setStoneType(StoneType type) { 
	std::lock_guard<std::mutex> lock(mutex);
	stoneType = type;
}