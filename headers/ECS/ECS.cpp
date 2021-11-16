#include "ECS.h"

void Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true; //Set mGroup bit in bitset
	manager.addToGroup(this, mGroup);
}