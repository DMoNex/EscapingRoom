#pragma once

#include "Block.h"
#include "Vec3.h"
#include "Renderer.h"
#include "World.h"
#include "Eye.h"

class World {
	// This will be used when the world is de-allocated.
	int sizeX, sizeY, sizeZ;
	Block*** map;
	// This is the location of Vec3(minX, minY, minZ) of map coord-system.
	// We can access to real coord by [i, j, k] + mapSstartPoint.
	Vec3 mapStartPoint;
	// This is the end coord of map. Vec3(maxX, maxY, maxZ)
	Vec3 mapEndPoint;
public:
	// Used for rendering of map.
	// Gravitational variation and rotations are defined in this variable.
	Eye eye;
private:
	// This only act over array, not real coord.
	Block getBlock(int, int, int) const;
	void setBlock(Block const&, int, int, int);;
public:
	~World();
	// The size of world must be included.
	World() : sizeX(0), sizeY(0), sizeZ(0) {}
	World(int, int, int);
	void init();
	void setMapStartPoint(Vec3 const&);
	void setMapEndPoint(Vec3 const&);
	// Unavailable access may return Block::AIR
	Block getBlock(Vec3 const&) const;
	Block getBlock(float, float, float) const;
	void setBlock(Block const&, Vec3 const&);
	void setBlock(Block const&, float, float, float);
	friend Renderer;
};