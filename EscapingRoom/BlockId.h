#pragma once

enum class BlockId {
	AIR, 			// 0
	ROOM,
	DOOR_CLOSED,
	DOOR_OPENED,
	WALL, 			
	STAIRS,			// 5
	PORTAL,
	LADDER,
	PAD,
	SWITCH,
	LASER_SENDER,	// 10
	LASER_RECEIVER,
	THORNS_TRAP_FIXED,
	ARROW_TRAP, 		// 13
};

enum class EntityId {
	PLAYER,			// 0
	BOX,
	BALLON,
	PRISM_BLOCK,
	MIRROR_BLOCK,
	THORNS_TRAP		// 5
};
