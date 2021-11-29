#pragma once
#include "pch.h"
#include "Block.h"
#include <string>
using namespace std;
class Data
{
public:
	int sizeX, sizeY, sizeZ;
	float mapStartX, mapStartY, mapStartZ;
	float playerSpawnX, playerSpawnY, playerSpawnZ;
	Block*** mapData;	//BlockId로 구성됨
public:
	Data(string const& path);
		~Data();
	//loadData함수로 파일에서 Data 객체의 인스턴스를 가져온 뒤, World클래스의 load함수를 통해 World->map을 채움.
	void load(string const&);
	void save(string const&);
	void free();
	void alloc();
};

