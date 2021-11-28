#include "pch.h"
#include "Renderer.h"
#include "EscapingRoomView.h"

#include <stdio.h>


#include "stb_image.h" // https://github.com/nothings/stb/blob/af1a5bc352164740c1cc1354942b1c6b72eacb8a/stb_image.h

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

#include "Vec3.h"

void Renderer::drawEntity() {
	World* currentWorld = CEscapingRoomView::game.getCurrentWorld();
	Vec3 centralizingVect;
	for (int i = 0; i < currentWorld->entityList.size(); i++) {
		centralizingVect = currentWorld->entityList[i]->getCentralizingVector();
		glPushMatrix();
		glTranslatef(currentWorld->entityList[i]->location.x,
			currentWorld->entityList[i]->location.y,
			currentWorld->entityList[i]->location.z);
		switch (currentWorld->entityList[i]->getEntityType()) {
		case EntityId::PLAYER:
			// Temporally using.
			centralizingVect = centralizingVect - currentWorld->eye.getInversedEyeMatrix() * centralizingVect;
			glTranslatef(centralizingVect.x, centralizingVect.y, centralizingVect.z);
			currentWorld->eye.rotateGLMatrix();
			// ERROR.
			drawCube(Entity(EntityId::PLAYER));
			glTranslatef(0, 1, 0);
			drawCube(Entity(EntityId::PLAYER));
			break;
		case EntityId::BOX:
			centralizingVect = centralizingVect - currentWorld->eye.getInversedEyeMatrix() * centralizingVect;
			glTranslatef(centralizingVect.x, centralizingVect.y, centralizingVect.z);
			currentWorld->eye.rotateGLMatrix();
			drawCube(Entity(EntityId::BOX));
			break;
		}
		glPopMatrix();
	}
}

void Renderer::drawSurface() {
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0); glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, 0, 0); glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 0, 1); glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, 1); glTexCoord2f(0.0f, 1.0f);
	glEnd();
}

void Renderer::drawCube(Block block) {
	switch (block.id) {
	case(BlockId::AIR):
	case(BlockId::DOOR_OPENED):
		break;
	case(BlockId::ROOM):
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->textureId[1]);
		break;
	case(BlockId::DOOR_CLOSED):
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->textureId[2]);
		break;
	case(BlockId::PORTAL):
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->textureId[6]);
		break;
	case(BlockId::PAD):
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->textureId[9]);
		break;
	}
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
	glBindTexture(GL_TEXTURE_2D, 0); // bind cancel
}
void Renderer::drawCube(Entity entity) {
	switch (entity.id) {
	case(EntityId::PLAYER): // empty block
	case(EntityId::BALLOON):
	case(EntityId::MIRROR_BLOCK):
	case(EntityId::PRISM_BLOCK):
	case(EntityId::THORNS_TRAP):
		break;
	case(EntityId::BOX): // BOX
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->entityTextureId[1]);
		break;
	}
	// Entity 확장시 각 면을 분리해서 활성화해야 할지도....?
	if (true) { // 아랫면 활성화 -> LOOP
		drawSurface();
	}
	if (true) { // 윗면 활성화 -> FLOOR
		glTranslatef(0, 1, 0);
		drawSurface();
		glTranslatef(0, -1, 0);
	}
	if (true) { // 왼면 활성화 -> RIGHT
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
	}
	if (true) { // 앞면 활성화 -> BACK
		glRotatef(90, 0, 0, 1);
		drawSurface();
		glRotatef(-90, 0, 0, 1);
	}
	if (true) { // 오른면 활성화 -> LEFT
		glTranslatef(0, 0, 1);
		glRotatef(-90, 1, 0, 0);
		drawSurface();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -1);
	}
	if (true) { // 뒷면 활성화 -> FRONT
		glTranslatef(1, 0, 0);
		glRotatef(90, 0, 0, 1);
		drawSurface();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-1, 0, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0); // bind cancel
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

void Renderer::makeTexture() {
	GLint i;
	unsigned char* data = 0;
	GLint width = 1024, height = 1024, nrChannels;
	//texture creat
	glGenTextures(14, CEscapingRoomView::game.getCurrentWorld()->textureId); // textureId 1~13 (0 == empty)
	for (i = 0; i < 14; i++) {
		//texture bind
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->textureId[i]);
		//set binded texture's option
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		switch (i) {
		case 0:
		case 3: // DOOR_Opened
			break;
		case 1: // ROOM
			data = stbi_load("image/ROOM.jpg", &width, &height, &nrChannels, 0);
			break;
		case 2: // DOOR_Closed
			data = stbi_load("image/DOOR.jpg", &width, &height, &nrChannels, 0);
			break;
		case 4:
		case 5:
		case 6: // portal
			data = stbi_load("image/PORTAL.jpg", &width, &height, &nrChannels, 0);
			break;
		case 7: // ladder
			break;
		case 8:
		case 9:
			data = stbi_load("image/PAD.jpg", &width, &height, &nrChannels, 0);
			break;
		case 10:
			break;
		}
		if (data) { // 유효성검사
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			
		}
		data = 0;
	}
	glGenTextures(6, CEscapingRoomView::game.getCurrentWorld()->entityTextureId); // textureId 1~6 (0 == empty)
	for (i = 0; i < 6; i++) { // create Entity Texture
		//texture Bind
		glBindTexture(GL_TEXTURE_2D, CEscapingRoomView::game.getCurrentWorld()->entityTextureId[i]);
		//set binded texture's option
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		switch (i) {
		case 0: // Player
		case 2: // Balloon
		case 3:
		case 4:
		case 5:
			break;
		case 1: // BOX
			data = stbi_load("image/BOX.jpg", &width, &height, &nrChannels, 0);
			break;
		}
		if (data) { // 유효성검사
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		}
		data = 0;
	}
}
/*		glBindTexture(GL_TEXTURE_2D, textureId[1]);		*/