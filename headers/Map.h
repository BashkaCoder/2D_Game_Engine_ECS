#pragma once

#include "Game.h"
#include "Utils.h"
#include <fstream>
#include <vector>

class Map {
public:

	Map();
	~Map();

	void loadMap(int mas[20][25]);
	void loadMapFromFile(const std::string& filename); //[20][25] 2d
	void drawMap();

private:

	SDL_Rect src, dest;
	//Todo: change to vector<SDL_Texture*>
	SDL_Texture* grass;
	SDL_Texture* sand;
	SDL_Texture* water;

	int map[20][25];

};
