#include "Application.h"
#include <thread>


Application::Application(const char* title, int width, int height)
	:window_width(width), window_height(height) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) { return; }
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) { return; }

	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_width, window_height,
		NULL
	);
	if (window == nullptr) { return; }

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) { return; }

	sdlInit = 1;
}
Application::~Application() {
	for (int i = 0; i < (int)(StoneType::TYPES_LENGTH); ++i) {
		SDL_DestroyTexture(stoneTextures[i]);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void swapSonesThFunk(SDL_Point& mbd, SDL_Event& ev, int squareSize, Game& game, int window_height, int window_width, bool& newThread) {
	newThread = 0;

	if (mbd.x / squareSize - ev.button.x / squareSize >= 1 && ev.button.x >= 0) {
		game.swapStones(mbd.x / squareSize, mbd.y / squareSize, mbd.x / squareSize - 1, mbd.y / squareSize);
	}
	else if (ev.button.x / squareSize - mbd.x / squareSize >= 1 && ev.button.x < window_width) {
		game.swapStones(mbd.x / squareSize, mbd.y / squareSize, mbd.x / squareSize + 1, mbd.y / squareSize);
	}
	else if (mbd.y / squareSize - ev.button.y / squareSize >= 1 && ev.button.y >= 0) {
		game.swapStones(mbd.x / squareSize, mbd.y / squareSize, mbd.x / squareSize, mbd.y / squareSize - 1);
	}
	else if (ev.button.y / squareSize - mbd.y / squareSize >= 1 && ev.button.y < window_height) {
		game.swapStones(mbd.x / squareSize, mbd.y / squareSize, mbd.x / squareSize, mbd.y / squareSize + 1);
	}

	newThread = 1;
}

void Application::startGame(int board_width, int board_height) {
	if (sdlInit == 0) {
		std::cout << "Window create failed!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return;
	}

	SDL_Rect displaySize;
	SDL_GetDisplayBounds(0, &displaySize);
	window_height = displaySize.h - (displaySize.h / 100) * 15;
	squareSize = window_height / board_height;
	window_width = board_width * squareSize;
	SDL_SetWindowSize(window, window_width, window_height);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	stoneTextures = new SDL_Texture * [(int)(StoneType::TYPES_LENGTH)];
	stoneTextures[(int)(StoneType::BLUE)] = IMG_LoadTexture(renderer, "assets/blue.png");
	stoneTextures[(int)(StoneType::RED)] = IMG_LoadTexture(renderer, "assets/red.png");
	stoneTextures[(int)(StoneType::GREEN)] = IMG_LoadTexture(renderer, "assets/green.png");
	stoneTextures[(int)(StoneType::YELLOW)] = IMG_LoadTexture(renderer, "assets/yellow.png");
	stoneTextures[(int)(StoneType::PURPLE)] = IMG_LoadTexture(renderer, "assets/purple.png");
	stoneTextures[(int)(StoneType::NONE)] = IMG_LoadTexture(renderer, "assets/none.png");

	for (int i = 0; i < (int)(StoneType::TYPES_LENGTH); ++i) {
		if (stoneTextures[i] == nullptr) {
			std::cout << "Texture init faild!" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return;
		}
	}

	game.createNewGame(board_width, board_height, squareSize);

	std::thread printerTh(&Application::printer, this);

	SDL_Event ev;
	SDL_Point mbd;
	std::thread swapStonesTh;
	bool newThread = 1;
	while (!exit) {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {

			case SDL_MOUSEBUTTONDOWN: {
				mbd.x = ev.button.x;
				mbd.y = ev.button.y;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				SDL_Event ev_temp = ev;
				if (newThread) {
					swapStonesTh = std::thread(swapSonesThFunk, std::ref(mbd), std::ref(ev_temp),
						squareSize, std::ref(game), window_height, window_width, std::ref(newThread));
					swapStonesTh.detach();
				}
				break;
			}
			case SDL_QUIT:
				exit = 1;
				break;
			}
		}
	}

	printerTh.join();
}

void Application::printer() {
	int board_width = game.getBoardWidth();
	int board_height = game.getBoardHeight();

	while (!exit) {

		//board
		SDL_SetRenderDrawColor(renderer, 35, 35, 35, 0);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 142, 137, 137, 0);
		// |||||
		for (int i = 1; i < board_width; ++i) {
			SDL_RenderDrawLine(renderer, squareSize * i, 0, squareSize * i, window_height);
		}
		// ====
		for (int i = 1; i < board_height; ++i) {
			SDL_RenderDrawLine(renderer, 0, squareSize * i, window_width, squareSize * i);
		}

		//stones
		for (int i = 0; i < board_width; ++i) {
			for (int j = 0; j < board_height; ++j) {
				Stone* stone = game.getStone(i, j);
				SDL_Rect rect = { stone->getWindow_x(), stone->getWindow_y(), squareSize, squareSize };
				SDL_RenderCopy(renderer, stoneTextures[(int)(stone->getStoneType())], 0, &rect);
			}
		}

		SDL_RenderPresent(renderer);
	}
}