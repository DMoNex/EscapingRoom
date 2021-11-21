#include "pch.h"
#include "Renderer.h"
#include "EscapingRoomView.h"

#include <stdio.h>

void Renderer::onDraw() {
	// For test.
	Block block(BlockId::ROOM, 0);
	Vec3 startPoint = CEscapingRoomView::world.mapStartPoint;
	Vec3 endPoint = CEscapingRoomView::world.mapEndPoint;
	for (float wx = -50; wx <= 50; wx++) {
		for (float wz = -50; wz <= 50; wz++) {
			CEscapingRoomView::world.setBlock(block, wx, 0.f, wz);
		}
	}
	// Cubic-Plane
	glPushMatrix();
	glTranslatef(startPoint.x, startPoint.y, startPoint.z);
	for (float wx = startPoint.x; wx <= endPoint.x; wx++) {
		for (float wy = startPoint.y; wy <= endPoint.y; wy++) {
			for (float wz = startPoint.z; wz <= endPoint.z; wz++) {
				drawCube(CEscapingRoomView::world.getBlock(wx, wy, wz));
				glTranslatef(0, 0, 1);
			}
			glTranslatef(0, 0, -(endPoint.z - startPoint.z + 1));
			glTranslatef(0, 1, 0);
		}
		glTranslatef(0, -(endPoint.y - startPoint.y + 1), 0);
		glTranslatef(1, 0, 0);
	}
	glPopMatrix();
	drawAxis();
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
	if (block.side[5]) {
		drawSurface();
	}
	if (block.side[0]) {
		glTranslatef(0, 1, 0);
		drawSurface();
		glTranslatef(0, -1, 0);
	}
	if (block.side[3]) {
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
	}
	if (block.side[2]) {
		glRotatef(90, 0, 0, 1);
		drawSurface();
		glRotatef(-90, 0, 0, 1);
	}
	if (block.side[1]) {
		glTranslatef(0, 0, 1);
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -1);
	}
	if (block.side[4]) {
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
