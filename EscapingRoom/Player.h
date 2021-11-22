#pragma once

#include "Entity.h"
#include "Vec3.h"

// Keyboard controlled-entity.
class Player : public Entity {
public:
	// is player pressing a key?
	bool keyW;
	bool keyS;
	bool keyA;
	bool keyD;
	// TODO: Grabbing and placing
	// Moving speed per tick.
	float speed;
public:
	virtual ~Player() {}
	Player() : Entity(EntityId::PLAYER), speed(0.1), keyW(false), keyS(false), keyA(false), keyD(false) {}
	virtual Entity* getPointingEntity() {
		return NULL;
	}
	// Controlling using keyboard wasd.
	void control(bool, bool, bool, bool);
	void resetKey();
	Vec3 getDirection();
};