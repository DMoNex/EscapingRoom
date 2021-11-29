#include "pch.h"
#include "Model.h"

Model::Model(int size) {
	this->size = size;
	if (size)
		init();
}

Model::~Model() {
	free();
}

void Model::alloc() {
	singleton = new Block * *[size];
	for (int i = 0; i < size; i++) {
		singleton[i] = new Block * [size * 2];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size * 2; j++) {
			singleton[i][j] = new Block[size];
		}
	}
}

void Model::free() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size * 2; j++) {
			delete[] singleton[i][j];
		}
	}
	for (int i = 0; i < size; i++) {
		delete[] singleton[i];
	}
	delete[] singleton;
}

void Model::init() {
	alloc();
	for (int wx = 0; wx < size; wx++) {
		for (int wy = 0; wy < size * 2; wy++) {
			for (int wz = 0; wz < size; wz++) {
				// setBlock(BlockId::WALL, wx, wy, wz);
			}
		}
	}
}

void Model::setBlock(Block semiBlock, int x, int y, int z) {
	if (x < 0 || x > size - 1 ||
		y < 0 || y > size * 2 - 1 ||
		z < 0 || z > size - 1)
		return;
	singleton[x][y][z] = semiBlock;
	if (getBlock(x, y + 1, z).id != BlockId::AIR) {
		singleton[x][y][z].side[TOP] = 0;
		singleton[x][y + 1][z].side[BOTTOM] = 0;
	}
	if (getBlock(x, y - 1, z).id != BlockId::AIR) {
		singleton[x][y][z].side[BOTTOM] = 0;
		singleton[x][y - 1][z].side[TOP] = 0;
	}
	if (getBlock(x + 1, y, z).id != BlockId::AIR) {
		singleton[x][y][z].side[FORWARD] = 0;
		singleton[x + 1][y][z].side[BACK] = 0;
	}
	if (getBlock(x - 1, y, z).id != BlockId::AIR) {
		singleton[x][y][z].side[BACK] = 0;
		singleton[x - 1][y][z].side[FORWARD] = 0;
	}
	if (getBlock(x, y, z + 1).id != BlockId::AIR) {
		singleton[x][y][z].side[LEFT] = 0;
		singleton[x][y][z + 1].side[RIGHT] = 0;
	}
	if (getBlock(x, y, z - 1).id != BlockId::AIR) {
		singleton[x][y][z].side[RIGHT] = 0;
		singleton[x][y][z - 1].side[LEFT] = 0;
	}
}

Block Model::getBlock(int x, int y, int z) {
	if (x < 0 || x > size - 1 ||
		y < 0 || y > size * 2 - 1 ||
		z < 0 || z > size - 1)
		return Block::AIR;
	return singleton[x][y][z];
}

#include "EscapingRoomView.h"
void Model::draw() {
	glPushMatrix();
	for (float wx = 0; wx < size; wx++) {
		for (float wy = 0; wy < size * 2; wy++) {
			for (float wz = 0; wz < size; wz++) {
				CEscapingRoomView::renderSingleton.drawCube(getBlock(wx, wy, wz), 1.0f / size);
				glTranslatef(0, 0, 1.0f / size);
			}
			glTranslatef(0, 0, -1);
			glTranslatef(0, 1.0f / size, 0);
		}
		glTranslatef(0, -2, 0);
		glTranslatef(1.0f / size, 0, 0);
	}
	glPopMatrix();
}

#include <fstream>
void Model::load(std::string const& path) {
	std::ifstream istream(path);
	int id;
	istream >> size;
	free();
	alloc();
	for (int wy = 0; wy < size * 2; wy++) {
		for (int wx = size - 1; wx >= 0; wx--) {
			for (int wz = size - 1; wz >= 0; wz--) {
				istream >> id;
				singleton[wx][wy][wz] = (BlockId)id;
			}
		}
	}
	istream.close();
}

void Model::save(std::string const& path) {
	std::ofstream ostream(path);
	ostream << size;
	ostream << "\n";
	for (int wy = 0; wy < size * 2; wy++) {
		for (int wx = size - 1; wx >= 0; wx--) {
			for (int wz = size - 1; wz >= 0; wz--) {
				ostream << (int) singleton[wx][wy][wz].id;
				if (wz != 0)
					ostream << " ";
			}
			if (wx != 0)
				ostream << "\n";
		}
		if (wy != 2 * size - 1)
			ostream << "\n\n";
	}
	ostream.close();
}