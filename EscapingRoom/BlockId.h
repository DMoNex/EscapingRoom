#pragma once

enum class BlockId {
	AIR, 			// 0, empty
	ROOM,
	DOOR_CLOSED,
	DOOR_OPENED,	// empty
	WALL, 			
	STAIRS,			// 5
	PORTAL,
	LADDER,
	PAD,			
	SWITCH,
	LASER_SENDER,	// 10
	LASER_RECEIVER,
	THORNS_TRAP_FIXED,
	ARROW_TRAP 		// 13
};
