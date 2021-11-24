#pragma once
#include "Vec3.h"

class DirectLight {
	Vec3 dir;
	Vec3 color;

public:
	DirectLight();	//this->dir = normalize(dir)
	~DirectLight();
	void SendShader();
};



class PointLight {
	Vec3 pos;
	Vec3 color;
	float range;

public:
	PointLight();
	~PointLight();
	void SendShader();
};

/*
	point light, direct light
*/