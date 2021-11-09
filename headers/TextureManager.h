#pragma once

#include "Game.h"
#include "Utils.h"

//Don't instantiate
class TextureManager {
public:
	static SDL_Texture* loadTexture(const std::string& filename);
	static void Draw(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest);
private:
};
