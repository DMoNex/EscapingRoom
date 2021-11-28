#include "pch.h"
#include "Model.h"

Model::Model(int size) {
	this->size = size;
	init();
}

void Model::init() {

}

void Model::setBlock(int x, int y, int z) {

}

Block Model::getBlock(int x, int y, int z) {
	return Block::AIR;
}

void Model::draw() {
	/*
	glPushMatrix();
	for (float wx = 0; wx < size; wx++) {
		for (float wy = 0; wy < size * 2; wy++) {
			for (float wz = 0; wz < size; wz++) {
				drawCube(getBlock(wx, wy, wz), size);
				glTranslatef(0, 0, 1);
			}
			glTranslatef(0, 0, -(endPoint.z - startPoint.z + 1));
			glTranslatef(0, 1, 0);
		}
		glTranslatef(0, -(endPoint.y - startPoint.y + 1), 0);
		glTranslatef(1, 0, 0);
	}
	glPopMatrix();
	*/
}