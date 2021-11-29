#include "pch.h"
#include "Game.h"
#include "MainFrm.h"
#include "EscapingRoomView.h"

World* Game::emptyWorld;
Model* Game::playerModel;
int Game::playerModelId;

Game::Game() {
	Player* tempPlayer = new Player();
	emptyWorld = new World(0, 0, 0);
	emptyWorld->entityList.push_back(tempPlayer);
	emptyWorld->player = tempPlayer;
	currentWorldPhase = 0;
	init();
}

#define SIZE 20
#include "Model.h"
void Game::init() {
	// Currently only the basic world is loaded.
	pushWorld(new World(10, 10, 10));
	Player* player = new Player();
	Entity* box = new Entity(EntityId::BOX);
	box->location = Vec3(0, 0, 0);
	worldList[0]->entityList.push_back(player);
	worldList[0]->entityList.push_back(box);
	worldList[0]->player = player;
	getCurrentWorld()->connectPortal(0, 1);
	playerModel = new Model(SIZE);
	for (int wy = 0; wy < SIZE * 2; wy++) {
		for (int wx = SIZE - 1; wx >= 0; wx--) {
			for (int wz = SIZE - 1; wz >= 0; wz--) {
				float y = (float) wy / (SIZE - 1) * 2;
				float x = (float) (SIZE - wx + 1) / (SIZE - 1) * 2;
				float z = (float) (SIZE - wz + 1) / (SIZE - 1) * 2;
				x -= 1;
				z -= 1;
				y -= 2;
				if (abs(x) + abs(y / 2) + abs(z) <= 1) {
					playerModel->setBlock(Block(BlockId::WALL), wx, wy, wz);
				}
			}
		}
	}
	playerModel->save("player.txt");
}

void Game::onTick() {
	CEscapingRoomView::singleton->Invalidate(FALSE);
	CEscapingRoomView::singleton->UpdateWindow();
	entityTick();
	playerTick();
}

// Gravity moving part.
void Game::entityTick() {
	bool shouldCloseDoor = true;
	for (int i = 0; i < getCurrentWorld()->entityList.size(); i++) {
		getCurrentWorld()->entityList[i]->velocity = - 1 / 5.0f * getCurrentWorld()->eye.up;
		getCurrentWorld()->entityList[i]->moveTo(getCurrentWorld()->entityList[i]->location +
			getCurrentWorld()->entityList[i]->velocity);
		getCurrentWorld()->entityList[i]->velocity = Vec3(0, 0, 0);
		getCurrentWorld()->entityList[i]->portallingDelay = getCurrentWorld()->entityList[i]->portallingDelay > 0 ? getCurrentWorld()->entityList[i]->portallingDelay - 1 :
			getCurrentWorld()->entityList[i]->portallingDelay;
		if (getCurrentWorld()->entityList[i]->isSteppingPad) {
			shouldCloseDoor = false;
		}
	}
	if (shouldCloseDoor)
		getCurrentWorld()->closeDoor();
}

// Keyboard moving part
void Game::playerTick() {
	if (getPlayer()->getKeyboardMovingDirection().length() < 0.1f) return;
	getPlayer()->velocity + getPlayer()->speed * getPlayer()->getKeyboardMovingDirection();
	getPlayer()->moveTo(getPlayer()->location +
		getCurrentWorld()->eye.getEyeMatrix() * (getPlayer()->speed * getPlayer()->getKeyboardMovingDirection()));
	getPlayer()->resetKey();
}

void Game::pushWorld(World* world) {
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