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
	Block*** mapData;	//BlockId�� ������
public:
	Data(string const& path);
		~Data();
	//loadData�Լ��� ���Ͽ��� Data ��ü�� �ν��Ͻ��� ������ ��, WorldŬ������ load�Լ��� ���� World->map�� ä��.
	void load(string const&);
	void save(string const&);
	void free();
	void alloc();
};

