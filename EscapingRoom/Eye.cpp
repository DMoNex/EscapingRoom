#include "pch.h"
#include "Eye.h"
#include "Matrix.h"

Vec3 Eye::getLeft() {
	return up.cross(front).normalize();
}

void Eye::rotateGLMatrix() {
	Matrix mat;
	mat.c1 = front;
	mat.c2 = up;
	mat.c3 = getLeft();
	mat.mulToOpenGL();
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