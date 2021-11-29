#include "pch.h"
#include "Data.h"
#include <fstream>
using namespace std;
Data::Data(string const& path) {
	load(path);
}

Data::~Data() {
	free();
}

void Data::load(string const& path) {
	ifstream fin(path);
	int id;
	fin >> sizeX >> sizeY >> sizeZ >> mapStartX >> mapStartY >> mapStartZ >> playerSpawnX >> playerSpawnY >> playerSpawnZ;
	alloc();
	for (int y = 0; y < sizeY; y++) {
		for (int x = sizeX - 1; x >= 0; x--) {
			for (int z = sizeZ - 1; z >= 0; z--) {
				fin >> id;
				if (id == '\n') {
					fin >> id;
					z++;
					continue;
				}
				mapData[x][y][z] = (BlockId)id;
			}
		}
	}
	fin.close();
};


void Data::save(string const& path) {
	ofstream fout(path);
	fout << sizeX 
		<< sizeY 
		<< sizeZ 
		<< mapStartX 
		<< mapStartY 
		<< mapStartZ 
		<< playerSpawnX 
		<< playerSpawnY 
		<< playerSpawnZ << "\n";
	for (int y = 0; y < sizeY; y++) {
		for (int x = sizeX - 1; x >= 0; x--) {
			for (int z = sizeZ - 1; z >= 0; z--) {
				fout << (int)mapData[x][y][z].id;
				if (z != 0) fout << " ";
			}
			if (x != 0) fout << "\n";
		}
		if (y != sizeY) fout << "\n\n";
	}
	fout.close();
}

void Data::free() {
	if (mapData != NULL) {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				delete[] mapData[i][j];
			}
		}
		for (int i = 0; i < sizeX; i++) {
			delete[] mapData[i];
		}
		delete[] mapData;
	}
}

void Data::alloc() {
	mapData = new Block * *[sizeX];
	for (int i = 0; i < sizeX; i++) {
		mapData[i] = new Block * [sizeY];
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			mapData[i][j] = new Block[sizeZ];
		}
	}	
}