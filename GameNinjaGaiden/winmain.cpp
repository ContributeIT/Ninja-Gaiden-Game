#include <windows.h>
#include "GameWindow.h"
#include "Game.h"
#include "DXInput.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	bool done = false;

	GameWindow::getInstance()->initHandleWindow(hInstance, nShowCmd);

	HWND hWnd = GameWindow::getInstance()->getHandleWindow();
	
	// init direct input
	if (!Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error Initializing DirectInput", "Error", MB_OK);
	}

	Game::getInstance()->init();

	// vòng lặp chính
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Game loop
		Game::getInstance()->run();
	} 

	return msg.wParam;
}