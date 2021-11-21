#include "pch.h"
#include "World.h"
#include "EscapingRoomView.h"

World::~World() {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			delete[] map[i][j];
		}
	}
	for (int i = 0; i < sizeX; i++) {
		delete[] map[i];
	}
	delete[] map;
}

World::World(int sizeX, int sizeY, int sizeZ) {
	mapStartPoint = Vec3(-sizeX / 2, -sizeY / 2, -sizeZ / 2);
	mapEndPoint = Vec3((sizeX - 1) / 2, (sizeY - 1) / 2, (sizeZ - 1) / 2);
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->sizeZ = sizeZ;
	map = new Block * *[sizeX];
	for (int i = 0; i < sizeX; i++) {
		map[i] = new Block * [sizeY];
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			map[i][j] = new Block[sizeZ];
		}
	}
	init();
}

// Making a room
void World::init() {
	Block block(BlockId::ROOM, 0);
	for (int wx = 0; wx < sizeX; wx++) {
		for (int wy = 0; wy < sizeY; wy++) {
			for (int wz = 0; wz < sizeZ; wz++) {
				setBlock(block, wx, wy, wz);
			}
		}
	}
	for (int wx = 0; wx < sizeX; wx++) {
		for (int wy = 0; wy < sizeY; wy++) {
			for (int wz = 0; wz < sizeZ; wz++) {
				if (!getBlock(wx, wy, wz).isVisible())
					setBlock(Block::AIR, wx, wy, wz);
			}
		}
	}
}

void World::setMapStartPoint(Vec3 const& point) {
	mapStartPoint = point;
}

void World::setMapEndPoint(Vec3 const& point) {
	mapEndPoint = point;
}

Block World::getBlock(int x, int y, int z) const {
	if (x < 0 || y < 0 || z < 0 ||
		x >= sizeX || y >= sizeY || z >= sizeZ) return Block::AIR;
	return map[x][y][z];
}

void World::setBlock(Block const& block, int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 ||
		x >= sizeX || y >= sizeY || z >= sizeZ) return;
	map[x][y][z] = block;
	// TODO: side update for nearing blocks.
	// These codes are about removing sides which are nearing.
	if (getBlock(x, y + 1, z).id != BlockId::AIR) {
		map[x][y][z].side[0] = 0;
		map[x][y + 1][z].side[5] = 0;
	}
	if (getBlock(x, y - 1, z).id != BlockId::AIR) {
		map[x][y][z].side[5] = 0;
		map[x][y - 1][z].side[0] = 0;
	}
	if (getBlock(x + 1, y, z).id != BlockId::AIR) {
		map[x][y][z].side[4] = 0;
		map[x + 1][y][z].side[2] = 0;
	}
	if (getBlock(x - 1, y, z).id != BlockId::AIR) {
		map[x][y][z].side[2] = 0;
		map[x - 1][y][z].side[4] = 0;
	}
	if (getBlock(x, y, z + 1).id != BlockId::AIR) {
		map[x][y][z].side[1] = 0;
		map[x][y][z + 1].side[3] = 0;
	}
	if (getBlock(x, y, z - 1).id != BlockId::AIR) {
		map[x][y][z].side[3] = 0;
		map[x][y][z - 1].side[1] = 0;
	}
	// TODO: Annihilating a block which has no side to appear.
}

void World::setBlock(Block const& block, Vec3 const& loc) {
	setBlock(block, loc.x - mapStartPoint.x, loc.y - mapStartPoint.y, loc.z - mapStartPoint.z);
}

Block World::getBlock(Vec3 const& loc) const {
	return getBlock(loc.x - mapStartPoint.x, loc.y - mapStartPoint.y, loc.z - mapStartPoint.z);
}

void World::setBlock(Block const& block, float x, float y, float z) {
	setBlock(block, (int)(x - mapStartPoint.x), (int)(y - mapStartPoint.y), (int)(z - mapStartPoint.z));
}

Block World::getBlock(float x, float y, float z) const {
	return getBlock((int)(x - mapStartPoint.x), (int)(y - mapStartPoint.y), (int)(z - mapStartPoint.z));
}
