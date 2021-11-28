#pragma once

#include "Block.h"

class Renderer {
public:
	GLuint* textureId;
public:
	void onDraw();
	void drawCurrentWorld();
	void drawEntity();
	// Generalizing surface drawing for player modelling.
	void drawSurface(float = 1.0f, float = 1.0f);
	void drawCube(Block, float size = 1);
	void drawCube(Entity);
	void drawAxis();


	void makeTexture();
};