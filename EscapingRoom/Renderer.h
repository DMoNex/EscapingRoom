#pragma once

#include "Block.h"

class Renderer {
public:
	GLuint* textureId;
public:
	void onDraw();
	void drawCurrentWorld();
	void drawEntity();
	void drawSurface();
	void drawCube(Block);
	void drawAxis();


	void makeTexture();
};