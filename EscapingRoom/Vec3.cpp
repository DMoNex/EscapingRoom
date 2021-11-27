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

Vec3 minimum(Vec3 a, Vec3 b) {
	Vec3 m;
	m.x = min(a.x, b.x);
	m.y = min(a.y, b.y);
	m.z = min(a.z, b.z);
	return m;
}

Vec3 findMinima(std::vector<Vec3>& list) {
	if (list.size() == 0) return Vec3(0, 0, 0);
	Vec3 min = list[0];
	for (int i = 1; i < list.size(); i++) {
		min = minimum(min, list[i]);
	}
	return min;
}

#include "EscapingRoomView.h"
// Transforming and appropriating to Vec3(0, 0, 0) vector lists(collising points).
void ucsRotation(std::vector<Vec3>& list) {
	for (int i = 0; i < list.size(); i++) {
		list[i] = CEscapingRoomView::game.getCurrentWorld()->eye.getEyeMatrix() * list[i];
	}
	Vec3 min = findMinima(list);
	// Parallel transformation
	for (int i = 0; i < list.size(); i++) {
		list[i] = list[i] - min;
	}
}