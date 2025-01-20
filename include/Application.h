#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"


class Application {

private:
	bool sdlInit = 0;
	bool exit = 0;

	int window_width;
	int window_height;
	int squareSize;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Game game;
	SDL_Texture** stoneTextures;

	void printer();

public:
	Application(const char* title, int width, int height);
	~Application();

	void startGame(int width, int height);
};