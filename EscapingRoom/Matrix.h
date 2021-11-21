#pragma once

#include "Vec3.h"
#include "Eye.h"

class Matrix {
public:
	Vec3 c1, c2, c3;
public:
	Matrix() : c1(0, 0, 0), c2(0, 0, 0), c3(0, 0, 0) {}
	Matrix(Vec3 c1, Vec3 c2, Vec3 c3) : c1(c1), c2(c2), c3(c3) {}
	Vec3 operator*(Vec3);
	void mulToOpenGL();
};

Matrix operator*(Matrix, Matrix);