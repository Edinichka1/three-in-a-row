#include "Application.h"


int main(int args, char* argv[]) {

	Application app("myGame", 640, 480);
	app.startGame(10, 10);

	return 0;
}