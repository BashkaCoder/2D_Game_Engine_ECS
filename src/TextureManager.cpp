#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const std::string& filename) {
	SDL_Surface* tmp = IMG_Load(filename.c_str());
	SDL_Texture* result = SDL_CreateTextureFromSurface(Game::renderer, tmp);
	if (!result) {
		printError("Cannot create texture!: " + filename);
	}
	else {
		std::cout << "Texture[" + filename + "] has been successfully loaded" << std::endl;
	}
	SDL_FreeSurface(tmp);
	return result;
}

void TextureManager::Draw(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

