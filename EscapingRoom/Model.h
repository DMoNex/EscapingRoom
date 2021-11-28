#pragma once

#include "Block.h"
#include <string>
// Extending World to draw Model.
class Model {
	Block*** singleton;
	// sizeX = sizeZ, sizeY = 2 * sizeX
	int size;
public:
	Model(int size = 0);
	~Model();
	void alloc();
	void free();
	void init(); // loading included.
	// Removing contiguous side of blocks.
	void setBlock(Block, int, int, int);
	Block getBlock(int, int, int);
	void draw();
	void load(std::string const&);
	void save(std::string const&);
};