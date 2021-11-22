#pragma once

#define TICK 60

#include "World.h"
#include <vector>

#include "Player.h"

class Game {
	std::vector<World*> worldList;
	// Pointing to current world.
	int currentWorldPhase;
	// This can be used when the game is cleared.
	static World* emptyWorld;
public:
	Game();
	// Loading world data. This calls Loader of map data.
	void init();
	void onTick();
	void createWorld(World* world);
	World* getCurrentWorld();
	void gotoNextWorld();
	Player* getPlayer();
};