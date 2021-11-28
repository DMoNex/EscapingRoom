#include "pch.h"
#include "Data.h"
#pragma warning(disable: 4996)

void Data::loadData(char* filename) {
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("cannot open your file\n");
		return;
	}
	fscanf(fp, "%d %d %d %f %f %f %d %d %d", &sizeX, &sizeY, &sizeZ,
		&mapStartX, &mapStartY, &mapStartZ, &playerSpawnX, &playerSpawnY, &playerSpawnZ);
	mapData = new BlockId * *[sizeX];
	for (int x = 0; x < sizeX; x++) {
		mapData[x] = new BlockId * [sizeY];
		for (int y = 0; y < sizeY; y++) {
			mapData[x][y] = new BlockId[sizeZ];
		}
	}
	for (int y = 0; y < sizeY; y++) {
		for (int x = sizeX - 1; x >= 0; x--) {
			for (int z = sizeZ - 1; y >= 0; z--) {
				fscanf(fp, "%d", &mapData[x][y][z]);
			}
		}
	}
	fclose(fp);
};

//아직 작성중입니다
void Data::saveData(char* filename) {
	FILE* fp;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("cannot oepn your file\n");
		return;
	}

	fclose(fp);
}
