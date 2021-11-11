#pragma once

#include <string>
#include "SDL.h"
#include "ECS.h"
#include "Components.h"

class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(const std::string& _tag) {
		tag = _tag;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}


};

