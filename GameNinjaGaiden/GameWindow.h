#pragma once
#include <Windows.h>

class GameWindow
{
	HWND handleWindow;

	static GameWindow * instance;

public:
	GameWindow();
	~GameWindow();

	static GameWindow * getInstance();
	static LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void initHandleWindow(HINSTANCE hInstance, int nCmdShow);
	HWND getHandleWindow();
};

