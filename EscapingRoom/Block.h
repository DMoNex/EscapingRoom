#pragma once

#include "BlockId.h"
#include "Vec3.h"

// Don't keep type-safety.
enum Direction {
	TOP,		// 0
	BOTTOM,		// 1
	FORWARD,	// 2
	BACK,		// 3
	LEFT,		// 4
	RIGHT		// 5
};

class Entity;

class Block { // Block은 모두 중력의 영향을 받지 않는다.
public:
	BlockId id;
	// If the side is to be drawn.
	char side[6]; // TOP / BOTTOM / FOWARD / BACK / LEFT / RIGHT
	char align;
	BOOL caseCrash; // false : can't crash / true : can crash
	BOOL lightTransmission; // false : 차단(그림자), true : 투과
public:
	static Block AIR;
	static Block LOOP; 
	static Block FLOOR;
	static Block LEFT_WALL;
	static Block RIGHT_WALL;
	static Block FRONT_WALL;
	static Block BACK_WALL;

	// ROOM : 천장/벽/바닥 나눠서 static으로 구현하는지?
public:
	bool isVisible();
	Block() : id(BlockId::AIR), align(0) {
		caseCrash = false;
		lightTransmission = true;
		for (int i = 0; i < 6; i++)
			side[i] = 0;
	}
	Block(BlockId id, int align = 0) : id(id), align(align % 6) {
		for (int i = 0; i < 6; i++) {
			side[i] = !((id == BlockId::AIR) || (id == BlockId::ROOM) || (id == BlockId::DOOR_CLOSED) ||
						(id == BlockId::PORTAL) || (id == BlockId::PAD));
		}
		switch (this->id) {
		case BlockId::AIR:
			caseCrash = false;
			break;
		case BlockId::DOOR_OPENED:
			side[align] = 1;
			caseCrash = true;
			lightTransmission = false;
			break;
		case BlockId::LADDER:
		case BlockId::SWITCH:
		case BlockId::LASER_SENDER:
		case BlockId::LASER_RECEIVER:
		case BlockId::THORNS_TRAP_FIXED:
			caseCrash = false;
			lightTransmission = true;
			break;
		case BlockId::PORTAL:
			side[align] = 1;
			caseCrash = true;
			lightTransmission = true;
			break;
		case BlockId::PAD:
			caseCrash = true;
			lightTransmission = true;
			side[align] = 1;
			break;
		case BlockId::ARROW_TRAP:
			caseCrash = false;
			lightTransmission = false;
			break;
		case BlockId::DOOR_CLOSED:
			caseCrash = true;
			lightTransmission = true;
			side[align] = 1;
			break;
		case BlockId::WALL:
		case BlockId::STAIRS:
			caseCrash = true;
			lightTransmission = false;
			break;
		case BlockId::ROOM: // ROOM은 한 면만 활성화
			side[align] = 1;
			caseCrash = true;
			lightTransmission = false;
			break;
		}
	}
	bool isCrashable();
	Vec3 getNormal();
	Vec3 getNormalBySide();
};