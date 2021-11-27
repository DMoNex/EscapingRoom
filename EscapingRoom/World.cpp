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
	this->nextPortalNum = 0;
	this->nextPortalGen = 0;
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
	eye = Eye();
	cameraInit();
}

// Making a room
void World::init() {
	Block closedDoor(BlockId::DOOR_CLOSED);
	Block openedDoor(BlockId::DOOR_OPENED);
	Block portalUp(BlockId::PORTAL_UP);
	Block portalDown(BlockId::PORTAL_DOWN);
	Block pad(BlockId::PAD);
	
	for (int wx = 0; wx < sizeX; wx++) {
		for (int wy = 0; wy < sizeY; wy++) {
			for (int wz = 0; wz < sizeZ; wz++) {
				if ((wx == 0 || wx == sizeX - 1) && (wy == 0 || wy == sizeY - 1) && (wz == 0 || wz == sizeZ - 1)) {
					// 각 꼭짓점 (8개) 투명
					setBlock(Block::AIR, wx, wy, wz);
				}
				//PORTAL for test
				else if (wx == sizeX - 1 && wy == 1 && wz == 4) {
					setBlock(portalDown, wx, wy, wz);
					makePortal(wx, wy, wz);
				}
				else if (wx == sizeX - 1 && wy == 2 && wz == 4) {
					setBlock(portalUp, wx, wy, wz);
				}
				// DOOR for test
				else if (wx == sizeX - 1 && (wy == 1 || wy == 2) && wz == 3) {
					setBlock(closedDoor, wx, wy, wz);
				}
				else if (wx == sizeX - 1 && (wy == 1 || wy == 2) && wz == 6) {
					setBlock(openedDoor, wx, wy, wz);
				}
				//PAD for test
				else if (wx == 2 && wy == 0 && wz == 4) {
					setBlock(pad, wx, wy, wz);
				}
				else if (wy == 0 && wx > 0 && wx < sizeX - 1 && wz > 0 && wz < sizeZ - 1) {
					// Range of Floor : ([1,sizeX-2], [1,sizeZ-2])
					setBlock(Block::FLOOR, wx, wy, wz);
				}
				else if (wx == 0 && wy > 0 && wy < sizeY - 1 && wz > 0 && wz < sizeY - 1) {
					setBlock(Block::FRONT_WALL, wx, wy, wz);
				}
				else if (wx == sizeX - 1 && wy > 0 && wy < sizeY - 1 && wz > 0 && wz < sizeY - 1) {
					setBlock(Block::BACK_WALL, wx, wy, wz);
				}
				else if (wz == 0 && wx > 0 && wx < sizeX - 1 && wy > 0 && wy < sizeY - 1) {
					setBlock(Block::LEFT_WALL, wx, wy, wz);
				}
				else if (wz == sizeZ - 1 && wx > 0 && wx < sizeX - 1 && wy > 0 && wy < sizeY - 1) {
					setBlock(Block::RIGHT_WALL, wx, wy, wz);
				}
				else if (wy == sizeY - 1 && wx > 0 && wx < sizeX - 1 && wz > 0 && wz < sizeY - 1) {
					setBlock(Block::LOOP, wx, wy, wz);
				}
			}
		}
	}
}

void World::cameraInit() {
	camera = 1 / 2.0f * (mapEndPoint + mapStartPoint + Vec3(1, 1, 1)) - sqrt(sizeX * sizeX + sizeY * sizeY + sizeZ * sizeZ) * eye.front;
}

void World::setMapStartPoint(Vec3 const& point) {
	mapStartPoint = point;
}

void World::setMapEndPoint(Vec3 const& point) {
	mapEndPoint = point;
}

Block World::getBlock(int x, int y, int z) const {
	/*
	// Error by float type itself -It comes from definition of Eye- cannot be fixed.
	// Rotating map..
	Vec3 minVect(0, 0, 0);
	Vec3 maxVect(sizeX - 1, sizeY - 1, sizeZ - 1);
	Matrix mat;
	mat.c1 = eye.front;
	mat.c2 = eye.up;
	mat.c3 = eye.left;
	maxVect = mat * maxVect;
	// Fixing error occured due to rotation.
	Vec3 errVect;
	errVect.x = min(minVect.x, maxVect.x);
	errVect.y = min(minVect.y, maxVect.y);
	errVect.z = min(minVect.z, maxVect.z);
	Vec3 blockLoc = (mat * Vec3(x, y, z)) - errVect;
	x = blockLoc.x;
	y = blockLoc.y;
	z = blockLoc.z;
	*/
	if (x < 0 || y < 0 || z < 0 ||
		x >= sizeX || y >= sizeY || z >= sizeZ) return Block::AIR;
	return map[x][y][z];
}

void World::setBlock(Block const& block, int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 ||
		x >= sizeX || y >= sizeY || z >= sizeZ) return;
	map[x][y][z] = block;
	/*
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
	*/
}

// Eye is acting to change the location to the rotated one.
void World::setBlock(Block const& block, Vec3 const& loc) {
	setBlock(block, (int)(loc.x - mapStartPoint.x), (int)(loc.y - mapStartPoint.y), (int)(loc.z - mapStartPoint.z));
}

// Eye is acting to change the location to the rotated one.
Block World::getBlock(Vec3 const& loc) const {
	return getBlock((int)(loc.x - mapStartPoint.x), (int)(loc.y - mapStartPoint.y), (int)(loc.z - mapStartPoint.z));
}

void World::setBlock(Block const& block, float x, float y, float z) {
	Vec3 vect;
	vect.x = x;
	vect.y = y;
	vect.z = z;
	setBlock(block, vect);
}

Block World::getBlock(float x, float y, float z) const {
	Vec3 vect;
	vect.x = x;
	vect.y = y;
	vect.z = z;
	return getBlock(vect);
}

void World::rotateFL() {
	Vec3 front = eye.front;
	Vec3 left = eye.left;
	eye.front = cos(PI / 2) * front + sin(PI / 2) * left;
	eye.left = -sin(PI / 2) * front + cos(PI / 2) * left;
	cameraInit();
}

void World::rotateLU() {
	Vec3 left = eye.left;
	Vec3 up = eye.up;
	eye.left = cos(PI / 2) * left + sin(PI / 2) * up;
	eye.up = -sin(PI / 2) * left + cos(PI / 2) * up;
	cameraInit();
}

void World::onCollisingWithBlockAndEntity(Entity* entity, Vec3 location) {
	if (getBlock(location).id != BlockId::ROOM) {
		LOG("COLLISING BLOCK ID: " + std::to_string((int)getBlock(location).id));
		// TODO: Portal event, PAD event
		if (getBlock(location).id == BlockId::DOOR_OPENED) {
			// When the player is entering a opened door: game closing.
			CEscapingRoomView::game.gotoNextWorld();
		}
	}
}

std::vector<Entity*> World::getEntityList() {
	return entityList;
}

void World::makePortal(int x, int y, int z) {
	if (nextPortalNum < 5) { // Portal Num Max : 5
		portalInfo[nextPortalNum][nextPortalGen][0] = x;
		portalInfo[nextPortalNum][nextPortalGen][1] = y;
		portalInfo[nextPortalNum++][nextPortalGen++][2] = z;
		nextPortalGen %= 2;
	}
}