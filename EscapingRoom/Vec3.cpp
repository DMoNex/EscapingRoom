#include "pch.h"
#include "Vec3.h"

Vec3 Vec3::operator+(Vec3 const& v) {
	Vec3 v2;
	v2.x = x + v.x;
	v2.y = y + v.y;
	v2.z = z + v.z;
	return v2;
}

Vec3 Vec3::operator-(Vec3 const& v) {
	Vec3 v2;
	v2.x = x - v.x;
	v2.y = y - v.y;
	v2.z = z - v.z;
	return v2;
}

float Vec3::dot(Vec3 v) {
	return x * v.x + y * v.y + z * v.z;
}

#include <cmath>

float Vec3::length() {
	return sqrt(x * x + y * y + z * z);
}

Vec3& Vec3::normalize() {
	(*this) = 1 / length() * (*this);
	return (*this);
}

Vec3 Vec3::cross(Vec3 const& v) {
	Vec3 v2;
	v2.x = y * v.z - z * v.y;
	v2.y = z * v.x - x * v.z;
	v2.z = x * v.y - y * v.x;
	return v2;
}

Vec3 operator*(float c, Vec3 v) {
	Vec3 v2;
	v2.x = v.x * c;
	v2.y = v.y * c;
	v2.z = v.z * c;
	return v2;
}