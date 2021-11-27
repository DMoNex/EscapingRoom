#include "pch.h"
#include "Player.h"

void Player::control(bool w, bool s, bool a, bool d) {
	keyW = w;
	keyS = s;
	keyA = a;
	keyD = d;
}

void Player::resetKey() {
	keyW = false;
	keyA = false;
	keyS = false;
	keyD = false;
}

#include "EscapingRoomView.h"

Entity* Player::getPointingEntity(float radius) {
	// TODO: Get some poining entity in available radius.
	std::vector<Entity*>& nearingEntities = getNearingEntities(radius);
	if (nearingEntities.size() == 0) return NULL;
	// Direction of player is equals with world eye.front.
	Eye playerEye = CEscapingRoomView::game.getCurrentWorld()->eye;
	Vec3 diff;
	Vec3 diff2;
	float angle;
	Entity* nearestEntity = nearingEntities[0];

	// Used to point the center of entity or player.
	Vec3 playerCentralizingVect(0.5, 1.0, 0.5);
	Vec3 entityCentralizingVect(0.5, 0.5, 0.5);
	for (int i = 0; i < nearingEntities.size(); i++) {
		diff = nearingEntities[i]->location + entityCentralizingVect - (this->location + playerCentralizingVect);
		diff2 = nearestEntity->location + entityCentralizingVect - (this->location + playerCentralizingVect);
		if (diff.length() < diff2.length())
			nearestEntity = nearingEntities[i];
	}

	return nearestEntity;
}

Vec3 Player::getKeyboardMovingDirection() {
	Vec3 direction(0, 0, 0);
	if (keyW) {
		direction = direction + Vec3(1, 0, 0);
	}
	if (keyS) {
		direction = direction + Vec3(-1, 0, 0);
	}
	if (keyA) {
		direction = direction + Vec3(0, 0, -1);
	}
	if (keyD) {
		direction = direction + Vec3(0, 0, 1);
	}
	if (direction.length() > 0.3) {
		direction.normalize(); // Got buggy when length = 0
	}
	return direction;
}

void Player::initCollisionPoints() {
	collisingPoints.clear();
	collisingPoints.push_back(Vec3(0, 0, 0));
	collisingPoints.push_back(Vec3(1, 0, 0));
	collisingPoints.push_back(Vec3(0, 2, 0));
	collisingPoints.push_back(Vec3(0, 0, 1));
}

void Player::grab() {
	Entity* pointingEntity = getPointingEntity(2.0f);
	if (pointingEntity) {
		LOG("POINTING ENITTY ID: " + std::to_string((int)pointingEntity->getEntityType()));
	}
}

Vec3 Player::getCentralizingVector() {
	return Vec3(0.5, 1.0, 0.5);
}