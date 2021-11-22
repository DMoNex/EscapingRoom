#pragma once

#define TICK 60
#define PI 3.141592653

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
	// Gravitization.
	void entityTick();
	// Moving by player will
	void playerTick();
	void createWorld(World* world);
	void rotateWorldLeft();
	void rotateWorldUp();
	World* getCurrentWorld();
	void gotoNextWorld();
	Player* getPlayer();
};