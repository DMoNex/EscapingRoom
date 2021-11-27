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
	collisingPoints.push_back(Vec3(0, 0, 0));
	collisingPoints.push_back(Vec3(1, 0, 0));
	collisingPoints.push_back(Vec3(0, 2, 0));
	collisingPoints.push_back(Vec3(0, 0, 1));
}

// We don't use this code.
#include "EscapingRoomView.h"
void Player::onSteppingBlock() {
	std::vector<Vec3> newCollisingPoints;
	newCollisingPoints.push_back(Vec3(0, 0, 0));
	newCollisingPoints.push_back(Vec3(1, 0, 0));
	newCollisingPoints.push_back(Vec3(0, 1, 0));
	newCollisingPoints.push_back(Vec3(0, 0, 1));
	for (int i = 0; i < newCollisingPoints.size(); i++) {
		newCollisingPoints[i] = CEscapingRoomView::game.getCurrentWorld()->eye.getEyeMatrix() * (newCollisingPoints[i] - Vec3(0.5, 0.5, 0.5) + CEscapingRoomView::game.getCurrentWorld()->eye.getInversedEyeMatrix() * Vec3(0.5, 0.5, 0.5));
	}
	for (int i = 0; i < collisingPoints.size(); i++) {
		collisingPoints[i] = newCollisingPoints[i];
	}
}