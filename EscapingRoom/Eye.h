#pragma once

#include "Vec3.h"
#include "Matrix.h"

// This eye can turn 360 degree!
class Eye {
public:
	Vec3 front;
	Vec3 up;
	Vec3 left;
public:
	Eye() : front(Vec3(1, 0, 0)), up(Vec3(0, 1, 0)), left(Vec3(0, 0, 1)) {}
	Eye(Vec3 front, Vec3 up) : front(front.normalize()), up(up.normalize()), left(getLeft()) {}
	Vec3 getLeft();
	Matrix getEyeMatrix();
	void rotateGLMatrix();
	void turnLeft(float angle);
	void stareUp(float angle);
	void rotate(float yaw, float pitch);
};