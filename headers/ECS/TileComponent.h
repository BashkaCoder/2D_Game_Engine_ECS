#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	std::string path;

	TileComponent() = default;

	TileComponent(int x, int y, int h, int w, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.h = h;
		tileRect.w = w;
		tileID = id;
	
		switch (tileID)
		{
		case 0:
			path = "res/water.png";
			break;
		case 1:
			path = "res/grass.png";
			break;
		case 2:
			path = "res/sand.png";
			break;
		default:
			printError("Incorrect tileID!");
			path = "res/water.png";
			break;
		}
	}

	void init() override {
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, 
												 (float)tileRect.h, (float)tileRect.w, 1);
		transform = &entity->getComponent<TransformComponent>();
	
		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}

};
