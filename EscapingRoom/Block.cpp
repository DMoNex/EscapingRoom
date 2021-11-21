#include "pch.h"
#include "Block.h"

Block Block::AIR(BlockId::AIR, 0);
Block Block::LOOP(BlockId::ROOM, 1);
Block Block::FLOOR(BlockId::ROOM, 0);
Block Block::LEFT_WALL(BlockId::ROOM, 5); // -> Left Wall이면 반댓면(Right side)활성화 ... 
Block Block::RIGHT_WALL(BlockId::ROOM, 4);
Block Block::FORWARD_WALL(BlockId::ROOM, 3);
Block Block::BACK_WALL(BlockId::ROOM, 2);

bool Block::isVisible() {
	bool ret = true;
	for (int i = 0; i < 6; i++) {
		ret |= side[i];
	}
	if (id == BlockId::AIR) ret = false;
	return ret;
}
