#include "GameObject.h"


GameObject::GameObject(const std::string& texturesheet, int x , int y) {
	xpos = x;
	ypos = y;
	objTexture = TextureManager::loadTexture(texturesheet.c_str());
}
GameObject::~GameObject() {
	SDL_DestroyTexture(objTexture);
}
void GameObject::update() {
	xpos++;
	ypos++;

	srcRect.w = srcRect.h = 100;
	srcRect.x = srcRect.y = 0;

	dstRect.x = xpos;
	dstRect.y = ypos;
	dstRect.w = srcRect.w * 2;
	dstRect.h = srcRect.h * 2;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}
