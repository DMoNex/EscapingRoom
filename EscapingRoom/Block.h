#pragma once

#include "BlockId.h"

class Block {
public:
	BlockId id;
	// If the side is to be drawn.
	char side[6];
public:
	static Block AIR;
public:
	Block() : id(BlockId::AIR) {
		for (int i = 0; i < 6; i++)
			side[i] = 0;
	}
	Block(BlockId id) : id(id) {
		for (int i = 0; i < 6; i++) {
			side[i] = !(id == BlockId::AIR);
		}
	}
	bool isVisible();
};