#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Utils.h"
#include <iostream>
#include <vector>

class ColliderComponent;

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

	static void AddTile(int id, int x, int y);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	bool isRunning;
	SDL_Window *window;
};

