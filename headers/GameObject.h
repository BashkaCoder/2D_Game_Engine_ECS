#pragma once
#include "Game.h"
#include "TextureManager.h"

class GameObject {
public:
	GameObject(const std::string& texturesheet, int x = 0, int y = 0);
	~GameObject();

	void update();
	void render();

private:
	int xpos, ypos;

	SDL_Rect srcRect, dstRect;
	SDL_Texture* objTexture;

};

