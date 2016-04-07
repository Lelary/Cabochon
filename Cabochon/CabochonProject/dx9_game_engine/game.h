// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.

#ifndef _GAME_H
#define _GAME_H
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "game_error.h"
#include "text_dx.h"
#include "console.h"

namespace gameNS
{
	const wchar_t FONT[] = TEXT("Courier New");
	const int POINT_SIZE = 14;
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 255, 255);
}

class Game
{
protected :
	Graphics* graphics;
	Input* input;
	Console* console;
	HWND hwnd;
	HRESULT hr;

	// ���� ī����
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;

	float frameTime;	// ������ �����ӿ� �ʿ��� �ð�.
	float fps;
	TextDX dxFont;
	bool fpsOn;

	DWORD sleepTime;	// ������ ���̿� ��ٸ� �и��� ���� �ð�
	bool paused;
	bool initialized;

	std::wstring command;

public :
	Game();
	virtual ~Game();

	// ������ �޽��� �ڵ鷯.
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void initialize(HWND hwnd);

	// WinMain�� ���� �޽��� �������� �ݺ������� ȣ���.
	virtual void run(HWND);

	// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
	virtual void releaseAll();

	// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
	virtual void resetAll();

	// ����� ��� �޸𸮸� �����Ѵ�.
	virtual void deleteAll();

	// �ܼ� ����� ó���Ѵ�.
	virtual void consoleCommand();

	// ���� �������� ������ �Ѵ�.
	virtual void renderGame();

	// �ν�Ʈ ���°� �� �׷��� ����̽��� ó���Ѵ�.
	virtual void handleLostGraphicsDevice();

	Graphics* getGraphics(){ return graphics; }
	Input* getInput() { return input; }
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	/*
		Pure Virtual Function Difinition.
	*/

	// ���� �������� �����Ѵ�.
	virtual void update() = 0;

	// AI ����� �����Ѵ�.
	virtual void ai() = 0;

	// �浹�� Ȯ���Ѵ�.
	virtual void collisions() = 0;

	/*
		�׷����� ������ �Ѵ�.
		graphics->spriteBegin();�� ȣ���Ѵ�.
		��������Ʈ�� �׸���.
		graphics->spriteEnd()�� ȣ���Ѵ�.
		��������Ʈ�� �ƴ� �͵��� �׸���.
	*/
	virtual void render() = 0;
};
#endif