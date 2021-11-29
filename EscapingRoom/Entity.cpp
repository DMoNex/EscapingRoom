#include "pch.h"
#include "Entity.h"

#include "EscapingRoomView.h"
Entity::Entity(EntityId id) {
	this->id = id;
	portallingDelay = 0;
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
	case EntityId::BALLOON:
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
	collisingPoints.clear();
	collisingPoints.push_back(Vec3(0, 0, 0));
	collisingPoints.push_back(Vec3(1, 0, 0));
	collisingPoints.push_back(Vec3(0, 1, 0));
	collisingPoints.push_back(Vec3(0, 0, 1));
}

bool Entity::isCrashable() {
	return caseCrash;
}

bool Entity::canFly() {
	return flight;
}

#include "EscapingRoomView.h"
void Entity::teleport(Vec3 location) {
	this->location = location;
}

// Chekcing whether at least one collising point is collising.
bool checkCollision(std::vector<Vec3>& list, Entity* entity) {
	bool isCollising = false;
	bool steppingPad = false;
	bool isCollisingWithPortal = false;
	bool isSteppingPortal = false;
	for (int i = 0; i < list.size(); i++) {
		if (CEscapingRoomView::game.getCurrentWorld()->getBlock(list[i] + entity->location).isCrashable()) {
			CEscapingRoomView::game.getCurrentWorld()->onCollisingWithBlockAndEntity(entity, entity->location + list[i]);
			isCollising = true;
			if (CEscapingRoomView::game.getCurrentWorld()->getBlock(list[i] + entity->location).id == BlockId::PORTAL)
				isCollisingWithPortal = true;
			if (CEscapingRoomView::game.getCurrentWorld()->getBlock(list[i] + entity->location).id == BlockId::PAD)
				steppingPad = true;
		}
	}
	entity->isSteppingPad = steppingPad;
	entity->portaled = isCollisingWithPortal + !entity->portaled + isSteppingPortal;
	return isCollising;
}

void printVector(Vec3& v) {
	// LOG("(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")");
}

void printVectorList(std::vector<Vec3>& list) {
	for (int i = 0; i < list.size(); i++) {
		printVector(list[i]);
	}
}

// Exactness of collision checking
#define PRECISION 100.0f
void Entity::moveTo(Vec3 location) {
	Vec3 centralizingVect = getCentralizingVector();
	if (isCrashable()) {
		Vec3 diff = location - this->location;
		std::vector<Vec3> temp;
		for (int i = 0; i < collisingPoints.size(); i++) {
			temp.push_back(CEscapingRoomView::game.getCurrentWorld()->eye.getEyeMatrix() * (collisingPoints[i] - centralizingVect + CEscapingRoomView::game.getCurrentWorld()->eye.getInversedEyeMatrix() * centralizingVect));
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

bool Entity::isPlayer() {
	return id == EntityId::PLAYER;
}

std::vector<Entity*> Entity::getNearingEntities(float radius) {
	std::vector<Entity*> nearingEntities;

	for (int i = 0; i < CEscapingRoomView::game.getCurrentWorld()->getEntityList().size(); i++) {
		Entity* indexedEntity = CEscapingRoomView::game.getCurrentWorld()->getEntityList()[i];
		Vec3 centralizingVect = Vec3(0.5, 0.5, 0.5);
		// Excepting self.
		if (indexedEntity == this) continue;
		if (indexedEntity->getEntityType() == EntityId::PLAYER)
			centralizingVect = Vec3(0.5, 1.0, 0.5);
		if ((indexedEntity->location - this->location + centralizingVect).length() <= radius)
			nearingEntities.push_back(indexedEntity);
	}

	return nearingEntities;
}

Vec3 Entity::getCentralizingVector() {
	return Vec3(0.5, 0.5, 0.5);
}