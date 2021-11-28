#pragma once

class Vec3 {
public:
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3 operator+(Vec3 const&);
	Vec3 operator-(Vec3 const&);
	float dot(Vec3);
	float length();
	Vec3& normalize();
	Vec3 cross(Vec3 const&);
	Vec3 gramSchmidting(Vec3);
};

Vec3 operator*(float, Vec3);
Vec3 minimum(Vec3, Vec3);

#include <vector>
Vec3 findMinima(std::vector<Vec3>&);
void ucsRotation(std::vector<Vec3>&);