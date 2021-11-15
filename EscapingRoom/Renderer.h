#pragma once

#include "Block.h"

class Renderer {
public:
	// RendererStream& operator<<(Model& models); can be included.
	void onDraw();
	void drawSurface();
	void drawCube(Block);
	void drawAxis();
};