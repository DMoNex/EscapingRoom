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
	initCollisionPoints();
}

void Entity::initCollisionPoints() {
	collisingPoints.push_back(Vec3(0, 0, 0));
	collisingPoints.push_back(Vec3(1, 0, 0));
	collisingPoints.push_back(Vec3(1, 0, 1));
	collisingPoints.push_back(Vec3(0, 0, 1));
	collisingPoints.push_back(Vec3(0, 1, 0));
	collisingPoints.push_back(Vec3(1, 1, 0));
	collisingPoints.push_back(Vec3(1, 1, 1));
	collisingPoints.push_back(Vec3(0, 1, 1));
}

bool Entity::isCrashable() {
	return caseCrash;
}

#include "EscapingRoomView.h"
void Entity::teleport(Vec3 location) {
	this->location = location;
}

// Chekcing whether at least one collising point is collising.
bool checkCollision(std::vector<Vec3>& list, Entity* entity) {
	for (int i = 0; i < list.size(); i++) {
		if (CEscapingRoomView::game.getCurrentWorld()->getBlock(list[i] + entity->location).isCrashable()) {
			CEscapingRoomView::game.getCurrentWorld()->onCollisingWithBlockAndEntity(entity, entity->location + list[i]);
			return true;
		}
	}
	return false;
}

void printVector(Vec3& v) {
	LOG("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
}

void printVectorList(std::vector<Vec3>& list) {
	for (int i = 0; i < list.size(); i++) {
		printVector(list[i]);
	}
}

// Exactness of collision checking
#define PRECISION 100.0f
void Entity::moveTo(Vec3 location) {
	if (isCrashable()) {
		Vec3 diff = location - this->location;
		std::vector<Vec3> temp;
		for (int i = 0; i < collisingPoints.size(); i++) {
			temp.push_back(CEscapingRoomView::game.getCurrentWorld()->eye.getEyeMatrix() * (collisingPoints[i] - Vec3(0.5, 1.0, 0.5) + CEscapingRoomView::game.getCurrentWorld()->eye.getInversedEyeMatrix() * Vec3(0.5, 1.0, 0.5)));
		}

		for (int i = 0; i < PRECISION; i++) {
			teleport(this->location + ((1.0f / PRECISION) * diff));
			if (checkCollision(temp, this)) {
				teleport(this->location - ((1.0f / PRECISION) * diff));
				/*
				if (CEscapingRoomView::game.getCurrentWorld()->getBlock(this->location - 1 / 5.0f * CEscapingRoomView::game.getCurrentWorld()->eye.up).isCrashable()) {
					onSteppingBlock(this->location - 1 / 5.0f * CEscapingRoomView::game.getCurrentWorld()->eye.up);
					LOG("Stepping");
				}
				*/
				break;
			}
		}
	}
	else {
		this->location = location;
	}
}

void Entity::onSteppingBlock(Vec3 vect) {

}

void Entity::moving() {

}