#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	return bool(
			rectA.x + rectA.w >= rectB.x &&
			rectB.x + rectB.w >= rectA.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.y + rectB.h >= rectA.y
			);
}