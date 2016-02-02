// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 2. Ch 3.

#define _CRTDBG_MAP_ALLOC // 메모리 누수를 탐지하기 위해.
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h> // 메모리 누수를 탐지하기 위해.
#include <crtdbg.h> // 메모리 누수를 탐지하기 위해.
#include "spacewar.h"

int WINAPI WinMain(HINSTANCE , HINSTANCE,  LPSTR, int);
bool CreateMainWindow(HWND&, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
/*
	뮤텍스를 이용하여 이 프로그램의 다른 인스턴스를 발견 할 시 true 반환.
	미사용.
*/
bool AnotherInstance();

Spacewar *game = NULL;
HWND hwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// 디버그 모드로 빌드 시 메모리 누수를 확인한다. 
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHCK_DF);
#endif

	MSG msg;
	
	game = new Spacewar;

	// 윈도우 생성.
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
		return 1;
	
	try {
		// game 객체 초기화, GameError를 던진다.
		game->initialize(hwnd);

		//메인 메시지 루프
		int done = 0;
		while (!done)
		{
			// 논 블로킹 메소드
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					done = 1;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				game->run(hwnd);
		}
		SAFE_DELETE(game);
		return msg.wParam;
	}
	catch (const GameError& err)
	{
		game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		game->deleteAll();
		DestroyWindow(hwnd);
		MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
	}

	SAFE_DELETE(game);
	return 0;
}

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->messageHandler(hwnd, msg, wParam, lParam));
}

bool CreateMainWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;

	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WinProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = CLASS_NAME;
	wcx.hIconSm = NULL;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	// 전체 화면이나 창화면을 설정한다.
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hwnd = CreateWindow(
		CLASS_NAME,
		GAME_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GAME_WIDTH,
		GAME_HEIGHT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		(LPVOID)NULL
	);

	if (!hwnd)
		return false;

	if (!FULLSCREEN)
	{
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);

		//hwnd, left, top, right, bottom, repaint
		MoveWindow(hwnd, 0, 0, GAME_WIDTH + (GAME_WIDTH - clientRect.right), GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), TRUE);
	}

	ShowWindow(hwnd, nCmdShow);

	return true;
}
bool AnotherInstance()
{
	HANDLE ourMutex;
	ourMutex = CreateMutex(NULL, true, MUTEX_STRING);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;

	return false;
}