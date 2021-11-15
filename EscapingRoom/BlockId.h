#pragma once

enum class BlockId {
	AIR, 			// 0
	ROOM,
	PLAYER,
	DOOR_CLOSED,
	DOOR_OPENED,
	WALL, 			// 5
	STAIRS,
	PORTAL,
	LADDER,
	PAD,
	BOX, 			// 10
	BALLOON,
	SWITCH,
	LASER_SENDER,
	LASER_RECEIVER,
	PRISM_BLOCK, 		// 15
	MIRROR_BLOCK,
	THORNS_TRAP,
	THORNS_TRAP_FIXED,
	ARROW_TRAP 		// 19
};
