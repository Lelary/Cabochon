// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 4.
// 코드의 일부는 책에 나와있지 않아, 소스코드를 위의 레퍼런스에서 다운받아 복사함.

#ifndef _INPUT_H
#define _INPUT_H
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include "constants.h"
#include "game_error.h"

// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif

namespace inputNS
{
	const int KEYS_ARRAY_LEN = 256;     // size of key arrays

	// what values for clear(), bit flag
	const UCHAR KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
	const UCHAR MOUSE = 4;
	const UCHAR TEXT_IN = 8;
	const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}


class Input
{
private:
	// 특정 키를 누른 경우 true가 된다.
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	// 게임 루프가 동작하는 동안 특정 키를 누르고 있는 경우 true가 된다. 
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::wstring textIn;			// 사용자가 입력한 텍스트.
	char charIn;				// 마지막에 입력한 문자.
	bool newLine;				// 새로운 줄을 시작할 때 true가 된다.
	int mouseX, mouseY;			// 화면 상에서의 마우스 위치.
	int mouseRawX, mouseRawY;	// 고정밀 마우스 데이터.
	RAWINPUTDEVICE Rid[1];		// 고정밀 마우스 용.
	bool mouseCaptured;			// 마우스가 캡처 된 경우 true.
	
	// 각각의 마우스 버튼이 눌렸을 경우 true.
	bool mouseLButton;
	bool mouseMButton;
	bool mouseRButton;
	bool mouseX1Button;
	bool mouseX2Button;

public:
	Input();
	~Input();
	
	/*
	 mouse와 controller의 입력을 초기화 한다.
	 GameError 를 던짐.
	 이전 : hwnd = window handle
			capture = 마우스를 캡처하려한다면 true
	*/
	void initialize(HWND hwnd, bool capture);
	
	/*
		키보드 입력 메소드.
	*/
	void keyDown(WPARAM wParam);
	void keyUp(WPARAM wParam);
	void keyIn(WPARAM wParam);
	bool isKeyDown(UCHAR vkey) const;
	bool wasKeyPressed(UCHAR vkey) const;
	bool anyKeyPressed() const;
	void clearKeyPress(UCHAR vkey);
	void clear(UCHAR what);
	void clearAll();

	void clearTextIn();
	std::wstring getTextIn(){ return textIn; }
	char getCharIn(){ return charIn; }

	/*
		마우스 입력 메소드.
	*/
	void mouseIn(LPARAM lParam);
	void mouseRawIn(LPARAM lParam);

	void setMouseLButton(bool b){ mouseLButton = b; }
	void setMouseMButton(bool b){ mouseMButton = b; }
	void setMouseRButton(bool b){ mouseRButton = b; }
	void setMouseXButton(WPARAM wParam);

	int getMouseX() const { return mouseX; }
	int getMouseY() const { return mouseY; }
	int getMouseRawX() const { return mouseRawX; }
	int getMouseRawY() const { return mouseRawY; }
	bool getMouseLButton() const { return mouseLButton; }
	bool getMouseMButton() const { return mouseMButton; }
	bool getMouseRButton() const { return mouseRButton; }
	bool getMouseX1Button() const { return mouseX1Button; }
	bool getMouseX2Button() const { return mouseX2Button; }


};

#endif