#pragma once

#include "SDL.h"
#include "ECS/Components.h"
#include "TextureManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	
	SDL_Rect srcRect, destRect;

public:
	SDL_Texture* texture;
	SpriteComponent() = default;
	SpriteComponent(const std::string& path) {
		setTexture(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const std::string& path) {
		texture = TextureManager::loadTexture(path);
	}


	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width; // check res/out.png (800x800 / 8)
		srcRect.h = transform->height;
	}
	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}


};
