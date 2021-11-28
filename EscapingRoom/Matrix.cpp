#include "pch.h"
#include "Matrix.h"

Vec3 Matrix::operator*(Vec3 v) {
	Vec3 v2;
	v2.x = c1.x * v.x + c2.x * v.y + c3.x * v.z;
	v2.y = c1.y * v.x + c2.y * v.y + c3.y * v.z;
	v2.z = c1.z * v.x + c2.z * v.y + c3.z * v.z;
	return v2;
}

Matrix operator*(Matrix m1, Matrix m2) {
	Matrix m3;
	m3.c1 = m1 * m2.c1;
	m3.c2 = m1 * m2.c2;
	m3.c3 = m1 * m2.c3;
	return m3;
}

void Matrix::mulToOpenGL() {
	float m[16] = {
		c1.x, c1.y, c1.z, 0,
		c2.x, c2.y, c2.z, 0,
		c3.x, c3.y, c3.z, 0,
		0,	  0,	0,	  1
	};
	glMultMatrixf(m);
}