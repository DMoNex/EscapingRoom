#pragma once

#include "Entity.h"

// Keyboard controlled-entity.
class Player : public Entity {
public:
	// TODO: Grabbing and placing
public:
	virtual ~Player() {}
	Player() : Entity(EntityId::PLAYER) {}
};