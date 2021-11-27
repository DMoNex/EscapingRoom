#include "pch.h"
#include "Eye.h"

Vec3 Eye::getLeft() {
	return (-1) * up.cross(front).normalize();
}

Matrix Eye::getEyeMatrix() {
	Matrix mat;
	mat.c1 = front;
	mat.c2 = up;
	mat.c3 = left;
	return mat;
}

void swap(float& a, float& b) {
	float temp = a;
	a = b;
	b = temp;
}

// Transposing the rotation matrix.
Matrix Eye::getInversedEyeMatrix() {
	Matrix& mat = getEyeMatrix();
	swap(mat.c1.y, mat.c2.x);
	swap(mat.c1.z, mat.c3.x);
	swap(mat.c2.z, mat.c3.y);
	return mat;
}

void Eye::rotateGLMatrix() {
	getEyeMatrix().mulToOpenGL();
}

#include <cmath>
void Eye::turnLeft(float angle) {
	Vec3 newFront = cos(angle) * front + sin(angle) * left;
	Vec3 newLeft = -sin(angle) * front + cos(angle) * left;
	front = newFront;
	left = newLeft;
}

void Eye::stareUp(float angle) {
	Vec3 newFront = cos(angle) * front + sin(angle) * up;
	Vec3 newUp = -sin(angle) * front + cos(angle) * up;
	front = newFront;
	up = newUp;
}

void Eye::rotate(float yaw, float pitch) {
	turnLeft(yaw);
	stareUp(pitch);
}