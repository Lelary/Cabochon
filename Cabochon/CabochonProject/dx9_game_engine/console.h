// 2016. 2. 11.

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <string>
#include <deque>
#include "constants.h"
#include "text_dx.h"
#include "graphics.h"
#include "input.h"

namespace consoleNS
{
	const UINT WIDTH = 500;
	const UINT HEIGHT = 400;
	const UINT X = 5;
	const UINT Y = 5;
	const UINT MARGIN = 4;
	const wchar_t FONT[] = TEXT("Courier New");
	const int FONT_HEIGHT = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 128, 128, 128);
	const int MAX_LINES = 256;
}

class Console
{
private:
	Graphics* graphics;
	Input* input;
	TextDX dxFont;
	float x, y;
	int rows;
	std::wstring commandStr;
	std::wstring inputStr;
	std::deque<std::wstring> text;	// 콘솔 텍스트.
	RECT textRect;
	COLOR_ARGB fontColor;
	COLOR_ARGB backColor;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	int scrollAmount;
	bool initialized;
	bool visible;

public:
	Console();
	virtual ~Console();

	bool initialize(Graphics* g, Input* in);
	/*
		콘솔을 그린다.
		Pre : BeginScene / EndScene 내부.
	*/
	const void draw();
	void showHide();
	bool getVisible(){ return visible; }
	void show(){ visible = true; }
	void hide(){ visible = false; }
	/*
		콘솔에 텍스트를 추가한다.
		str에 있는 텍스트의 첫 번째 줄만 표시될 것이다.
	*/
	void print(const std::wstring& str);
	/*
		콘솔 명령을 반환한다.
		콘솔의 단일 키 명령을 처리한다.
		다른 모든 명령은 Game으로 반환한다.
	*/
	std::wstring getCommand();
	std::wstring getInput(){ return inputStr; }
	void clearInput(){ inputStr = TEXT(""); }

	void onLostDevice();
	void onResetDevice();

};

#endif //_CONSOLE_H