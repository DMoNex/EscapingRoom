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
	loadMap("test.txt");
	// getCurrentWorld()->connectPortal(0, 1);

	// Modelling player.
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

void Game::loadMap(std::string const& path) {
	Data* d = new Data("test.txt");
	World* world = new World(d->sizeX, d->sizeY, d->sizeZ);
	pushWorld(world);
	Player* player = new Player();
	Entity* box = new Entity(EntityId::BOX);
	world->setMapStartPoint(Vec3(d->mapStartX, d->mapStartY, d->mapStartZ));
	player->location = Vec3(d->playerSpawnX,d->playerSpawnY, d->playerSpawnZ);
	box->location = player->location;
	world->entityList.push_back(player);
	world->entityList.push_back(box);
	world->player = player;

	// World constructing.
	for (int wx = 0; wx < world->sizeX; wx++) {
		for (int wy = 0; wy < world->sizeX; wy++) {
			for (int wz = 0; wz < world->sizeX; wz++) {
				if ((wx == 0 || wx == world->sizeX - 1) && (wy == 0 || wy == world->sizeY - 1) && (wz == 0 || wz == world->sizeZ - 1)) {
					// 각 꼭짓점 (8개) 투명
					world->map[wx][wy][wz] = Block::AIR;
				}
				else if (wy == 0 && wx > 0 && wx < world->sizeX - 1 && wz > 0 && wz < world->sizeZ - 1) {
					// Range of Floor : ([1,sizeX-2], [1,sizeZ-2])
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, TOP);
				}
				else if (wx == 0 && wy > 0 && wy < world->sizeY - 1 && wz > 0 && wz < world->sizeY - 1) {
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, BACK);
				}
				else if (wx == world->sizeX - 1 && wy > 0 && wy < world->sizeY - 1 && wz > 0 && wz < world->sizeY - 1) {
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, FORWARD);
				}
				else if (wz == 0 && wx > 0 && wx < world->sizeX - 1 && wy > 0 && wy < world->sizeY - 1) {
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, RIGHT);
				}
				else if (wz == world->sizeZ - 1 && wx > 0 && wx < world->sizeX - 1 && wy > 0 && wy < world->sizeY - 1) {
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, LEFT);
				}
				else if (wy == world->sizeY - 1 && wx > 0 && wx < world->sizeX - 1 && wz > 0 && wz < world->sizeY - 1) {
					world->map[wx][wy][wz] = Block(d->mapData[wx][wy][wz].id, BOTTOM);
				}

				if (d->mapData[wx][wy][wz].id == BlockId::PORTAL)
					world->makePortal(wx, wy, wz);
				if (d->mapData[wx][wy][wz].id == BlockId::DOOR_CLOSED ||
					d->mapData[wx][wy][wz].id == BlockId::DOOR_OPENED) {
					world->door = world->map[wx][wy][wz];
					if (!world->isDoorGenerated) {
						world->doorLoc1 = { wx, wy, wz };
						world->isDoorGenerated = true;
					}
					else world->doorLoc2 = { wx,wy,wz };
				}
			}
		}
	}

	for (int i = 0; i < world->portalRelation.size(); i += 2) {
		world->connectPortal(i, i + 1);
	}

	delete d;
}