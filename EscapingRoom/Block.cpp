#include "pch.h"
#include "Block.h"

Block Block::AIR(BlockId::AIR, 0);
Block Block::LOOP(BlockId::ROOM, 1);
Block Block::FLOOR(BlockId::ROOM, 0);
Block Block::LEFT_WALL(BlockId::ROOM, 5); // -> Left Wall이면 반댓면(Right side)활성화 ... 
Block Block::RIGHT_WALL(BlockId::ROOM, 4);
Block Block::FRONT_WALL(BlockId::ROOM, 3);
Block Block::BACK_WALL(BlockId::ROOM, 2);

bool Block::isVisible() {
	bool ret = true;
	for (int i = 0; i < 6; i++) {
		ret |= side[i];
	}
	if (id == BlockId::AIR) ret = false;
	return ret;
}

bool Block::isCrashable() {
	return caseCrash;
}

Vec3 Block::getNormal() {
	switch (align) {
	case TOP:
		return Vec3(0, 1, 0);
		break;
	case BOTTOM:
		return Vec3(0, -1, 0);
		break;
	case FORWARD:
		return Vec3(1, 0, 0);
		break;
	case BACK:
		return Vec3(-1, 0, 0);
		break;
	case LEFT:
		return Vec3(0, 0, 1);
		break;
	case RIGHT:
		return Vec3(0, 0, -1);
		break;
	}
	return Vec3(0, 1, 0);
}