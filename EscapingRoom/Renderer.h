#pragma once

#include "Block.h"

class Renderer {
public:
	void onDraw();
	void drawSurface();
	void drawCube(Block);
	void drawAxis();
};