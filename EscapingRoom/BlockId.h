#pragma once

enum class BlockId {
	AIR, 			// 0, empty
	ROOM,
	DOOR_CLOSED,
	DOOR_OPENED,	// empty
	WALL, 			
	STAIRS,			// 5
	PORTAL_UP,
	PORTAL_DOWN,
	LADDER,
	PAD,			
	SWITCH,			// 10
	LASER_SENDER,
	LASER_RECEIVER,
	THORNS_TRAP_FIXED,
	ARROW_TRAP 		// 14
};
