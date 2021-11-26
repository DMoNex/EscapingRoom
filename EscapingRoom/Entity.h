#pragma once

#include "EntityId.h"
#include "Vec3.h"

#include <vector>
class Entity {
public:
	EntityId id;
	// If the side is to be drawn.
	char side[6]; // TOP / BOTTOM / FOWARD / BACK / LEFT / RIGHT
	bool/*BOOL*/ caseCrash; // false : can't crash / true : can crash
	char lightTransmission; // 0 : ����(�׸���), 1 : ����, 2 : ����, 3 : �ݻ�
	bool flight;
	Vec3 location;
	Vec3 velocity;
	// Vec3 acceleration; should we use this?
	// Relative to entity leg location meaing aligned by up vector.
	// It is recommended to give some minimum points as possible.
	std::vector<Vec3> collisingPoints;
public:
	virtual ~Entity() {}
	// Showing the entity is what.
	EntityId getEntityType();
	// A entity is pushed to world.entitylist with construction.
	Entity() : id(EntityId::PLAYER) {
		int i;
		for (i = 0; i < 6; i++) {
			side[i] = 0;
		}
		caseCrash = true;
		lightTransmission = 1;
		flight = false;
	}
	Entity(EntityId id); // It can be some long codes
	// Judging whether the flags such as crash and giving location.
	// Constructing internal part of Entity.
	void init();
	void initCollisionPoints();
	// Should entity also need this?
	// Needed for player grabbing entity/block
	virtual Entity* getPointingEntity() {
		return NULL;
	};
	bool isCrashable();
	// Unavailable movement will be blocked later.
	// This is same with teleportation which does not change velocity.
	void teleport(Vec3);
	void moveTo(Vec3);
	// This is a natural movement due to gravity or something.
	// Change velocity.
	void moving();
	// This will call moving.
	void gravitizing();
	void resetVelocity();
	// The value can be -1 or 0 or 1
	int getGravityDirection();
	virtual void onSteppingBlock(Vec3);
};