#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Utils.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const std::string& title, int x, int y, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	inline bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool isRunning;
	SDL_Window *window;
};

