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
	Entity* grabbingEntity;
	bool portaled;
public:
	virtual ~Player() {}
	Player() : Entity(EntityId::PLAYER), speed(0.1), keyW(false), keyS(false), keyA(false), keyD(false) {
		initCollisionPoints();
	}
	Entity* getPointingEntity(float);
	void initCollisionPoints();
	// Controlling using keyboard wasd.
	void control(bool, bool, bool, bool);
	void resetKey();
	void grab();
	// Releasing the grabbed entity.
	void release();
	Vec3 getKeyboardMovingDirection();
	Vec3 getCentralizingVector();
};