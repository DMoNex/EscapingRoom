#include "pch.h"
#include "Game.h"
#include "MainFrm.h"
#include "EscapingRoomView.h"

World* Game::emptyWorld = new World(0, 0, 0);

Game::Game() {
	currentWorldPhase = 0;
	init();
}

void Game::init() {
	// Currently only the basic world is loaded.
	createWorld(new World(10, 10, 10));
	Player* player = new Player();
	worldList[0]->entityList.push_back(player);
	worldList[0]->player = player;
}

void Game::rotateWorldLeft() {
	getCurrentWorld()->eye.turnLeft(PI / 2);
}

void Game::rotateWorldUp() {
	getCurrentWorld()->eye.stareUp(PI / 2);
}

void Game::onTick() {
	CEscapingRoomView::singleton->Invalidate(FALSE);
	CEscapingRoomView::singleton->UpdateWindow();
	entityTick();
	playerTick();
}

void Game::entityTick() {

}

void Game::playerTick() {
	// Vec3 vec3 = getPlayer()->getDirection();
	// LOG(std::to_string(vec3.x) + " " + std::to_string(vec3.y) + " " + std::to_string(vec3.z));
	getPlayer()->velocity + getPlayer()->speed * getPlayer()->getDirection();
	getPlayer()->moveTo(getPlayer()->location + 
		getPlayer()->velocity + 
		getPlayer()->speed * getPlayer()->getDirection());
	getPlayer()->resetKey();
}

void Game::createWorld(World* world) {
	worldList.push_back(world);
}

World* Game::getCurrentWorld() {
	// When the game pointer exceeds existing worlds.
	if (currentWorldPhase >= worldList.size()) return emptyWorld;
	return worldList[currentWorldPhase];
}

void Game::gotoNextWorld() {
	currentWorldPhase++;
}

Player* Game::getPlayer() {
	return getCurrentWorld()->player;
}