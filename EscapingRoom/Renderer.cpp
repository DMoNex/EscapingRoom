#include "pch.h"
#include "Renderer.h"
#include "EscapingRoomView.h"

#include <stdio.h>

void Renderer::onDraw() {
	drawCurrentWorld();
	drawEntity();
	drawAxis();
}

void Renderer::drawCurrentWorld() {
	// For test.
	Vec3 startPoint = CEscapingRoomView::game.getCurrentWorld()->mapStartPoint;
	Vec3 endPoint = CEscapingRoomView::game.getCurrentWorld()->mapEndPoint;
	// Drawing map
	// Cubic-Plane
	glPushMatrix();
	glTranslatef(startPoint.x, startPoint.y, startPoint.z);
	for (float wx = startPoint.x; wx <= endPoint.x; wx++) {
		for (float wy = startPoint.y; wy <= endPoint.y; wy++) {
			for (float wz = startPoint.z; wz <= endPoint.z; wz++) {
				drawCube(CEscapingRoomView::game.getCurrentWorld()->getBlock(wx, wy, wz));
				glTranslatef(0, 0, 1);
			}
			glTranslatef(0, 0, -(endPoint.z - startPoint.z + 1));
			glTranslatef(0, 1, 0);
		}
		glTranslatef(0, -(endPoint.y - startPoint.y + 1), 0);
		glTranslatef(1, 0, 0);
	}
	glPopMatrix();
}

void Renderer::drawEntity() {
	World* currentWorld = CEscapingRoomView::game.getCurrentWorld();
	for (int i = 0; i < currentWorld->entityList.size(); i++) {
		glPushMatrix();
		glTranslatef(currentWorld->entityList[i]->location.x,
			currentWorld->entityList[i]->location.y,
			currentWorld->entityList[i]->location.z);
		switch (currentWorld->entityList[i]->getEntityType()) {
		case EntityId::PLAYER:
			// Temporally using.
			drawCube(Block(BlockId::WALL));
			glTranslatef(0, 1, 0);
			drawCube(Block(BlockId::WALL));
			break;
		}
		glPopMatrix();
	}
}

void Renderer::drawSurface() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glEnd();
}

void Renderer::drawCube(Block block) {
	if (block.side[1]) { // 아랫면 활성화 -> LOOP
		drawSurface();
	}
	if (block.side[0]) { // 윗면 활성화 -> FLOOR
		glTranslatef(0, 1, 0);
		drawSurface();
		glTranslatef(0, -1, 0);
	}
	if (block.side[4]) { // 왼면 활성화 -> RIGHT
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
	}
	if (block.side[2]) { // 앞면 활성화 -> BACK
		glRotatef(90, 0, 0, 1);
		drawSurface();
		glRotatef(-90, 0, 0, 1);
	}
	if (block.side[5]) { // 오른면 활성화 -> LEFT
		glTranslatef(0, 0, 1);
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -1);
	}
	if (block.side[3]) { // 뒷면 활성화 -> FRONT
		glTranslatef(1, 0, 0);
		glRotatef(90, 0, 0, 1);
		drawSurface();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-1, 0, 0);
	}
}

void Renderer::drawAxis() {
	glBegin(GL_LINES);
	// x-axis
	glColor3f(1, 0, 0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	// y-axis
	glColor3f(0, 1, 0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	// z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();
}
