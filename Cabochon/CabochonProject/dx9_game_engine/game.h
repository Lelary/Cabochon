// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 4.

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

	// 성능 카운터
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;

	float frameTime;	// 마지막 프레임에 필요한 시간.
	float fps;
	TextDX dxFont;
	bool fpsOn;

	DWORD sleepTime;	// 프레임 사이에 기다릴 밀리초 단위 시간
	bool paused;
	bool initialized;

	std::wstring command;

public :
	Game();
	virtual ~Game();

	// 윈도우 메시지 핸들러.
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void initialize(HWND hwnd);

	// WinMain의 메인 메시지 루프에서 반복적으로 호출됨.
	virtual void run(HWND);

	// 그래픽 디바이스가 로스트 상태가 됐을 떄 호출됨. 예약된 모든 비디오 메모리를 해제하고 그래픽 디바이스를 리셋한다.
	virtual void releaseAll();

	// 모든 표면을 재생성 하고 모든 개체를 리셋한다.
	virtual void resetAll();

	// 예약된 모든 메모리를 삭제한다.
	virtual void deleteAll();

	// 콘솔 명령을 처리한다.
	virtual void consoleCommand();

	// 게임 아이템을 렌더링 한다.
	virtual void renderGame();

	// 로스트 상태가 된 그래픽 디바이스를 처리한다.
	virtual void handleLostGraphicsDevice();

	Graphics* getGraphics(){ return graphics; }
	Input* getInput() { return input; }
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	/*
		Pure Virtual Function Difinition.
	*/

	// 게임 아이템을 갱신한다.
	virtual void update() = 0;

	// AI 계산을 수행한다.
	virtual void ai() = 0;

	// 충돌을 확인한다.
	virtual void collisions() = 0;

	/*
		그래픽을 렌더링 한다.
		graphics->spriteBegin();을 호출한다.
		스프라이트를 그린다.
		graphics->spriteEnd()를 호출한다.
		스프라이트가 아닌 것들을 그린다.
	*/
	virtual void render() = 0;
};
#endif