#pragma once

#include "Block.h"
// Extending World to draw Model.
class Model {
	Block*** singleton;
	// sizeX = sizeZ, sizeY = 2 * sizeX
	int size;
public:
	Model(int size = 0);
	void init(); // loading included.
	// Removing contiguous side of blocks.
	void setBlock(int, int, int);
	Block getBlock(int, int, int);
	void draw();
};