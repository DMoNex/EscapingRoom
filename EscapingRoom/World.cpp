#include "pch.h"
#include "World.h"

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
}

void World::setMapStartPoint(Vec3 point) {
	mapStartPoint = point;
}

Block World::getBlock(int x, int y, int z) const {
	if (x < 0 || y < 0 || z < 0 ||
		x > sizeX || y > sizeY || z > sizeZ) return Block::AIR;
	return map[x][y][z];
}

void World::setBlock(Block const& block, int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 ||
		x > sizeX || y > sizeY || z > sizeZ) return;
	map[x][y][z] = block;
	// TODO: side update for nearing blocks.
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