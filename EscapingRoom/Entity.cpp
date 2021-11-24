#include "pch.h"
#include "Entity.h"

#include "EscapingRoomView.h"
Entity::Entity(EntityId id) {
	this->id = id;
	init();
}

EntityId Entity::getEntityType() {
	return id;
}

void Entity::init() {
	switch (id) {
	case EntityId::PLAYER:
		caseCrash = true;
		lightTransmission = false;
		break;
	}
}

bool Entity::isCrashable() {
	return caseCrash;
}

#include "EscapingRoomView.h"
void Entity::moveTo(Vec3 location) {
	if (isCrashable()) {
		int i;
		bool collisionState = false;
		// TODO: Preventing movement when the movement is not avilable.
		Vec3 directing = location - this->location;
		// when the directing is so small then ignore the moving.
		// Stucking bug must be fixed, Side detecting updated.
		if (directing.length() >= 0.01) {
			directing.normalize();
			for (i = 0; i <= directing.length(); i++) {
				if (CEscapingRoomView::game.getCurrentWorld()->getBlock(i * directing + this->location).id != BlockId::AIR) {
					collisionState = true;
					break;
				}
			}
			if (collisionState) {
				location = i * directing + this->location;
			}
			else {
				this->location = location;
			}
		}
	}
	else {
		this->location = location;
	}
}

void Entity::moving() {

}

void Entity::gravitizing() {
	velocity = velocity + getGravityDirection() * Vec3(0, 0.5, 0);
}

int Entity::getGravityDirection() {
	// this can be changed.
	return -1;
}