#include "pch.h"
#include "Block.h"

Block Block::AIR;

bool Block::isVisible() {
	bool ret = true;
	for (int i = 0; i < 6; i++) {
		ret |= side[i];
	}
	if (id == BlockId::AIR) ret = false;
	return ret;
}