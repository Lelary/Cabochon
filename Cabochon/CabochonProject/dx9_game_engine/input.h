// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.
// �ڵ��� �Ϻδ� å�� �������� �ʾ�, �ҽ��ڵ带 ���� ���۷������� �ٿ�޾� ������.

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
	// Ư�� Ű�� ���� ��� true�� �ȴ�.
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	// ���� ������ �����ϴ� ���� Ư�� Ű�� ������ �ִ� ��� true�� �ȴ�. 
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::wstring textIn;			// ����ڰ� �Է��� �ؽ�Ʈ.
	char charIn;				// �������� �Է��� ����.
	bool newLine;				// ���ο� ���� ������ �� true�� �ȴ�.
	int mouseX, mouseY;			// ȭ�� �󿡼��� ���콺 ��ġ.
	int mouseRawX, mouseRawY;	// ������ ���콺 ������.
	RAWINPUTDEVICE Rid[1];		// ������ ���콺 ��.
	bool mouseCaptured;			// ���콺�� ĸó �� ��� true.
	
	// ������ ���콺 ��ư�� ������ ��� true.
	bool mouseLButton;
	bool mouseMButton;
	bool mouseRButton;
	bool mouseX1Button;
	bool mouseX2Button;

public:
	Input();
	~Input();
	
	/*
	 mouse�� controller�� �Է��� �ʱ�ȭ �Ѵ�.
	 GameError �� ����.
	 ���� : hwnd = window handle
			capture = ���콺�� ĸó�Ϸ��Ѵٸ� true
	*/
	void initialize(HWND hwnd, bool capture);
	
	/*
		Ű���� �Է� �޼ҵ�.
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
		���콺 �Է� �޼ҵ�.
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