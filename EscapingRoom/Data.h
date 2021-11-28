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
	BlockId*** mapData;	//BlockId�� ������
public:
	Data() : sizeX(10), sizeY(10), sizeZ(10), mapStartX(-5), mapStartY(-5), mapStartZ(-5), playerSpawnX(0), playerSpawnY(0), playerSpawnZ(0), mapData(NULL) {};
	//loadData�Լ��� ���Ͽ��� Data ��ü�� �ν��Ͻ��� ������ ��, WorldŬ������ load�Լ��� ���� World->map�� ä��.
	void loadData(char* filename);
	void saveData(char* filename);
};

