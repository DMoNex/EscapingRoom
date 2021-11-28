#pragma once

class Portal {
public:
	int x, y, z; // Current location
	int nx, ny, nz; // Next location
public:
	Portal() : x(0), y(0), z(0), nx(0), ny(0), nz(0) {}
	void setLocation(int, int, int);
	void setNext(int, int, int);
};