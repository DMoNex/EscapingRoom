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

#include "EscapingRoomView.h"
void Entity::teleport(Vec3 location) {
	this->location = location;
}

void Entity::moveTo(Vec3 location) {
	bool crashingState = false;
	if (isCrashable()) {
		Vec3 collisingPoint = this->location + 0.5f * (CEscapingRoomView::game.getCurrentWorld()->eye.front + CEscapingRoomView::game.getCurrentWorld()->eye.left);
		Vec3 diff = location - this->location;
		Vec3 directing = (location - this->location).normalize();
		for (int i = 0; i < diff.length() * 100; i++) {
			if (!CEscapingRoomView::game.getCurrentWorld()->getBlock(0.01f * directing + collisingPoint).isCrashable())
				collisingPoint = collisingPoint + 0.01f * directing;
			else {
				crashingState = true;
				break;
			}
		}
		teleport(collisingPoint - 0.5f * (CEscapingRoomView::game.getCurrentWorld()->eye.front + CEscapingRoomView::game.getCurrentWorld()->eye.left));
		// Crashing callback
		if (crashingState) {
			CEscapingRoomView::game.getCurrentWorld()->onCollisingWithBlockAndEntity(this, collisingPoint = collisingPoint + 0.01f * directing);
		}
	}
	else {
		this->location = location;
	}
}

void Entity::moving() {

}