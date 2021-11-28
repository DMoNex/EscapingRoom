#pragma once
#include "pch.h"
#include <iostream>
#include "Block.h"

using namespace std;
class Data
{
public:
	int sizeX, sizeY, sizeZ;
	float mapStartX, mapStartY, mapStartZ;
	float playerSpawnX, playerSpawnY, playerSpawnZ;
	BlockId*** mapData;	//BlockId로 구성됨
public:
	Data() : sizeX(10), sizeY(10), sizeZ(10), mapStartX(-5), mapStartY(-5), mapStartZ(-5), playerSpawnX(0), playerSpawnY(0), playerSpawnZ(0), mapData(NULL) {};
	//loadData함수로 파일에서 Data 객체의 인스턴스를 가져온 뒤, World클래스의 load함수를 통해 World->map을 채움.
	void loadData(char* filename);
	void saveData(char* filename);
};

