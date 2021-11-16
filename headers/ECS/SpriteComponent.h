#pragma once

#include <map>

#include "SDL.h"

#include "ECS/Components.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "Animation.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<std::string, Animation> animations;

	SpriteComponent() = default;
	SpriteComponent(const std::string& path) {
		setTexture(path);
	}
	SpriteComponent(const std::string& path, bool isAnimated) {
		animated = isAnimated;

		Animation idle(0, 1, 100);
		Animation walkDown(0, 8, 100);
		Animation walkLeft(1, 8, 100);
		Animation walkRight(2, 8, 100);
		Animation walkUp(3, 8, 100);

		animations["Idle"] = idle;
		animations["WalkDown"] = walkDown;
		animations["WalkLeft"] = walkLeft;
		animations["WalkRight"] = walkRight;
		animations["WalkUp"] = walkUp;

		play("Idle");// Animation set
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

		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void play(const std::string& animationName) {
		frames = animations[animationName].frames;
		speed = animations[animationName].speed;
		animIndex = animations[animationName].index;
	}

};
