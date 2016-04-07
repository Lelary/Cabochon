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
	std::deque<std::wstring> text;	// �ܼ� �ؽ�Ʈ.
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
		�ܼ��� �׸���.
		Pre : BeginScene / EndScene ����.
	*/
	const void draw();
	void showHide();
	bool getVisible(){ return visible; }
	void show(){ visible = true; }
	void hide(){ visible = false; }
	/*
		�ֿܼ� �ؽ�Ʈ�� �߰��Ѵ�.
		str�� �ִ� �ؽ�Ʈ�� ù ��° �ٸ� ǥ�õ� ���̴�.
	*/
	void print(const std::wstring& str);
	/*
		�ܼ� ����� ��ȯ�Ѵ�.
		�ܼ��� ���� Ű ����� ó���Ѵ�.
		�ٸ� ��� ����� Game���� ��ȯ�Ѵ�.
	*/
	std::wstring getCommand();
	std::wstring getInput(){ return inputStr; }
	void clearInput(){ inputStr = TEXT(""); }

	void onLostDevice();
	void onResetDevice();

};

#endif //_CONSOLE_H