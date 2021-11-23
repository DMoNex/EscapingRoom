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
		lightTransmission = 1;
		flight = false;
		break;
	case EntityId::BOX:
		caseCrash = true;
		lightTransmission = 0;
		flight = false;
		break;
	case EntityId::BALLON:
		caseCrash = true;
		lightTransmission = 0;
		flight = true;
		break;
	case EntityId::PRISM_BLOCK:
		caseCrash = true;
		lightTransmission = 2; // ±¼Àý
		flight = false;
		break;
	case EntityId::MIRROR_BLOCK:
		caseCrash = true;
		lightTransmission = 3; // ¹Ý»ç
		flight = false;
		break;
	case EntityId::THORNS_TRAP:
		caseCrash = false;
		lightTransmission = 1;
		flight = false;
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