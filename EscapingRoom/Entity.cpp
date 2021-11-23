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

void Entity::moveTo(Vec3 location) {
	if (isCrashable()) {
		this->location = location;
		// TODO: Preventing movement when the movement is not avilable.
	}
	else {
		this->location = location;
	}
}

void Entity::moving() {

}

void Entity::gravitizing() {

}