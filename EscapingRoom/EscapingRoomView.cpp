
// EscapingRoomView.cpp: CEscapingRoomView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "EscapingRoom.h"
#endif

#include "EscapingRoomDoc.h"
#include "EscapingRoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Light.h"
Renderer CEscapingRoomView::renderSingleton;
// 10 by 10 by 10 to make it symmetric.
Game CEscapingRoomView::game;

// CEscapingRoomView

IMPLEMENT_DYNCREATE(CEscapingRoomView, CView)

BEGIN_MESSAGE_MAP(CEscapingRoomView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEscapingRoomView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CEscapingRoomView 생성/소멸

CEscapingRoomView* CEscapingRoomView::singleton = NULL;

CEscapingRoomView::CEscapingRoomView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	singleton = this;
}

CEscapingRoomView::~CEscapingRoomView()
{
}

BOOL CEscapingRoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

#include "Game.h"
bool CEscapingRoomView::isThreading = false;
CWinThread* CEscapingRoomView::gameThread = NULL;

UINT run(LPVOID param) {
	while (CEscapingRoomView::isThreading) {
		CEscapingRoomView::game.onTick();
		Sleep(1000.0f / TICK);
	}
	AfxEndThread(0);
	return 0;
}

void CEscapingRoomView::OnDraw(CDC* /*pDC*/)
{
	CEscapingRoomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	if (!gameThread) {
		isThreading = true;
		CEscapingRoomView::gameThread = AfxBeginThread(run, 0, 0);
	}

	// Invalidate(FALSE);
}


// CEscapingRoomView 인쇄


void CEscapingRoomView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEscapingRoomView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CEscapingRoomView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CEscapingRoomView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CEscapingRoomView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEscapingRoomView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEscapingRoomView 진단

#ifdef _DEBUG
void CEscapingRoomView::AssertValid() const {
	CView::AssertValid();
}

void CEscapingRoomView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

CEscapingRoomDoc* CEscapingRoomView::GetDocument() const { // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEscapingRoomDoc)));
	return (CEscapingRoomDoc*)m_pDocument;
}
#endif //_DEBUG


// CEscapingRoomView 메시지 처리기

// SetPixelformat
// desc : function to set the pixel format for the device context
//
BOOL CEscapingRoomView::SetDevicePixelFormat(HDC hdc) {
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,								// default version
		PFD_DRAW_TO_WINDOW |			// support window
		PFD_SUPPORT_OPENGL |			// support OpenGL
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,					// RGBA type
		32,								// 32-bit color depth
		0, 0, 0, 0, 0, 0,				// color bits ignored
		8,								// no alpha buffer
		0,								// shift bit ignored
		8,								// no accumulation buffer
		0, 0, 0, 0,						// accum bits ignored
		16,								// 16-bit z-buffer
		0,								// no stencil buffer
		0,								// no auxiliary buffer
		PFD_MAIN_PLANE,					// main layer
		0,								// reserved
		0, 0, 0							// layer masks ignored
	};

	//choose best matching pixel format
	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("ChoosePixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return false;
	}

	// set pixel format to device context
	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
		MessageBox(LPCTSTR("SetPixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return false;
	}
	return TRUE;
}

int CEscapingRoomView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_hDC = GetDC()->m_hDC;

	// set the pixel format
	if (!SetDevicePixelFormat(m_hDC)) {
		return -1;
	}

	// create rendering context and make it current
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);

	// initialize renderring mode
	InitGL();
	gameThread = 0;

	return 0;
}


void CEscapingRoomView::OnDestroy() {
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// deselect rendering context and delete it
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}
const static GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const static GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const static GLfloat LightPosition[] = { 0.0f, 0.0f, 15.0f, 1.0f };
void CEscapingRoomView::InitGL(GLvoid) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
}

void CEscapingRoomView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}

void CEscapingRoomView::ReSizeGLScene(GLsizei width, GLsizei height) {
	// don't want a divide by zero
	if (height == 0)
		height = 1;

	//reset the viewport to new dimensions
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// calculate aspect ratio of the window
	// gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, (game.getPlayer()->location - camera).length(), 1000.0f);

	//set modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

#include "MainFrm.h"
#include <sstream>

void CEscapingRoomView::DrawGLScene(void) {
	//clear screen and depth buffer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 2.0f, (game.getPlayer()->location - game.getCurrentWorld()->camera).length() - 0.5f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//camera view configuration
	gluLookAt(game.getCurrentWorld()->camera.x, game.getCurrentWorld()->camera.y, game.getCurrentWorld()->camera.z, 
		0, 0, 0, 
		game.getCurrentWorld()->eye.up.x, 
		game.getCurrentWorld()->eye.up.y, 
		game.getCurrentWorld()->eye.up.z);

	// How does the time is lapsing.
	// std::stringstream stream;
	// stream << time(NULL);
	// LOG(stream.str());

	renderSingleton.onDraw();

	//swap buffer
	SwapBuffers(m_hDC);
}

const wchar_t* c2w(const char* str, int len) {
	wchar_t* wt = (wchar_t*)malloc(sizeof(wchar_t) * ((long long)len + 1));
	for (int i = 0; i < len; i++) {
		wt[i] = str[i];
	}
	wt[len] = 0;
	return wt;
}

void CEscapingRoomView::printLog(std::string str) {
	const wchar_t* wt = c2w(str.c_str(), str.size());
	COutputWnd* wnd = CMainFrame::singleton->getOutputWindow();
	wnd->getDebugOutputList().AddString((LPCTSTR)wt);
	wnd->getDebugOutputList().SetTopIndex(wnd->getDebugOutputList().GetCount() - 1);
	free((void*)wt);
}

void CEscapingRoomView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	game.getPlayer()->control(GetKeyState('W') & 0x8000, 
		GetKeyState('S') & 0x8000, 
		GetKeyState('A') & 0x8000, 
		GetKeyState('D') & 0x8000);
	switch (nChar) {
	case VK_LEFT:
		game.getCurrentWorld()->rotateFL();
		break;
	case VK_RIGHT:
		game.getCurrentWorld()->rotateFL();
		game.getCurrentWorld()->rotateFL();
		game.getCurrentWorld()->rotateFL();
		break;
		// UP and DOWN will be disabled in real game playing.
	case VK_UP:
		game.getCurrentWorld()->rotateLU();
		break;
	case VK_DOWN:
		game.getCurrentWorld()->rotateLU();
		game.getCurrentWorld()->rotateLU();
		game.getCurrentWorld()->rotateLU();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
