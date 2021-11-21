#include "pch.h"
#include "Game.h"
#include "MainFrm.h"
#include "EscapingRoomView.h"

void Game::onTick() {
	LOG("Hi");
	AfxGetApp()->GetMainWnd()->Invalidate(FALSE);
	AfxGetApp()->GetMainWnd()->RedrawWindow();
}