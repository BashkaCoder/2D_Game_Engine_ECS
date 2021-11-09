#pragma once

#include "ECS/Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	//My tiles are 48x48 pixels
	int height = 48;
	int width = 48;
	int scale = 1;

	//SPEED
	int speed = 3; 

	TransformComponent() {
		position.Zero(); //обнуляем
	}
	TransformComponent(int sc) {
		position.Zero();
		scale = sc;
	}
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	int x() { return position.x; };
	int y() { return position.y; };
	void x(float x) { position.x = x; };
	void y(float y) { position.y = y; };

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
		//position += velocity * speed;
	}

	void setPos(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void setPos(const Vector2D& vec) {
		position.x = vec.x;
		position.y = vec.y;
	}
};

