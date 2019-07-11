#include "GameWindow.h"
#include "Game.h"
#include "DXInput.h"

#define WINDOW_CLASSNAME "GameWindow"
#define WINDOW_TITLE "Ninja Gaiden v6.9"

// scale 2.5 backbuffer với height x1.05
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 567

GameWindow::GameWindow()
{
}


GameWindow::~GameWindow()
{
}

GameWindow * GameWindow::instance = NULL;
GameWindow * GameWindow::getInstance()
{
	if (instance == NULL)
	{
		instance = new GameWindow();
	}
	return instance;
}

HWND GameWindow::getHandleWindow()
{
	return handleWindow;
}

void GameWindow::initHandleWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszClassName = WINDOW_CLASSNAME;
	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(
		WINDOW_CLASSNAME,
		WINDOW_TITLE,
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		0,	// default: CW_USEDEFAULT
		0,	// default: CW_USEDEFAULT
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->handleWindow = hWnd;
}

LRESULT WINAPI GameWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETFOCUS:
		if (dikeyboard != NULL) dikeyboard->Acquire();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
