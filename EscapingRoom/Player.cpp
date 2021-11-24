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