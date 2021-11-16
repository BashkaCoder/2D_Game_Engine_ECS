#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("WalkUp");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("WalkDown");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("WalkLeft");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("WalkRight");
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				sprite->play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				sprite->play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				sprite->play("Idle");
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				sprite->play("Idle");
				transform->velocity.x = 0;
				break;
			}
		}

	}

};