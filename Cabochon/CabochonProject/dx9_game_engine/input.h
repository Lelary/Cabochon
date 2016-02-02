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
#include <XInput.h>
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

const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0X7FFF);    // default to 20% of range as deadzone
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;                      // trigger range 0-255
const DWORD MAX_CONTROLLERS = 4;                                // Maximum number of controllers supported by XInput

// Bit corresponding to gamepad button in state.Gamepad.wButtons
const DWORD GAMEPAD_DPAD_UP = XINPUT_GAMEPAD_DPAD_UP;
const DWORD GAMEPAD_DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN;
const DWORD GAMEPAD_DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT;
const DWORD GAMEPAD_DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT;
const DWORD GAMEPAD_START_BUTTON = XINPUT_GAMEPAD_START;
const DWORD GAMEPAD_BACK_BUTTON = XINPUT_GAMEPAD_BACK;
const DWORD GAMEPAD_LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB;
const DWORD GAMEPAD_RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB;
const DWORD GAMEPAD_LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER;
const DWORD GAMEPAD_RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER;
const DWORD GAMEPAD_A = XINPUT_GAMEPAD_A;
const DWORD GAMEPAD_B = XINPUT_GAMEPAD_B;
const DWORD GAMEPAD_X = XINPUT_GAMEPAD_X;
const DWORD GAMEPAD_Y = XINPUT_GAMEPAD_Y;

struct ControllerState
{
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
	float vibrateTimeLeft;	// mSec
	float vibrateTimeRight;	// mSec
	bool connected;
};

class Input
{
private:
	// 특정 키를 누른 경우 true가 된다.
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	// 게임 루프가 동작하는 동안 특정 키를 누르고 있는 경우 true가 된다. 
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::string textIn;			// 사용자가 입력한 텍스트.
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

	//컨트롤러의 상태.
	ControllerState controllers[MAX_CONTROLLERS];

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
	std::string getTextIn(){ return textIn; }
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

	/*
		컨트롤러 입력 메소드.
	*/
	void checkControllers();
	void readControllers();
	const ControllerState* getControllerState(UINT n);
	const WORD getGamepadButtons(UINT n);

	/*
		컨트롤러 n 의 D 패드 버튼의 상태를 반환하는 함수들.
	*/
	bool getGamepadDPadUp(UINT n);
	bool getGamepadDPadDown(UINT n);
	bool getGamepadDPadLeft(UINT n);
	bool getGamepadDPadRight(UINT n);
	bool getGamepadStart(UINT n);
	bool getGamepadBack(UINT n);
	bool getGamepadLeftThumb(UINT n);
	bool getGamepadRightThumb(UINT n);
	bool getGamepadLeftShoulder(UINT n);
	bool getGamepadRightShoulder(UINT n);
	bool getGamepadA(UINT n);
	bool getGamepadB(UINT n);
	bool getGamepadX(UINT n);
	bool getGamepadY(UINT n);

	/*
		컨트롤러 n의
		아날로그 컨트롤러인 트리거의 상태를 반환하는 함수들.
		0~255 사이의 BYTE 값을 반환한다. 0은 뗀 상태를 표현하고, 255는 완전히 누른 상태를 표현한다.
		input.h 상단에 데드존이 명시되어 있다.
	*/
	BYTE getGamepadLeftTrigger(UINT n);
	BYTE getGamepadRightTrigger(UINT n);

	/*
		컨트롤러 n의
		아날로그 컨트롤인 썸스틱의 상태를 반환하는 함수들.
		SHORT 값은 썸스틱의 위치를 알려주는데, 각 축에 대해 -32,768 ~ 32,768 의 값으로 표현된다.
		0은 중앙을 의미한다. 
		input.h 상단에 데드존이 명시되어 있다.
	*/
	SHORT getGamepadThumbLX(UINT n);
	SHORT getGamepadThumbLY(UINT n);
	SHORT getGamepadThumbRX(UINT n);
	SHORT getGamepadThumbRY(UINT n);

	/*
		컨트롤러 n의 왼쪽 모터를 진동하게 만든다. 
		왼쪽은 낮은 진동수의 진동을 생성한다. 
		speed 0 = 사용하지 않음. 65536 = 100%.
		sec = 진동할 초단위 시간.
	*/
	void gamePadVibrateLeft(UINT n, WORD speed, float sec);
	/*
		컨트롤러 n의 오른쪽 모터를 진동하게 만든다.
		오른쪽은 높은 진동수의 진동을 생성한다.
		speed 0 = 사용하지 않음. 65536 = 100%.
		sec = 진동할 초단위 시간.
	*/
	void gamePadVibrateRight(UINT n, WORD speed, float sec);

	/*
		연결된 컨트롤러를 진동하게 만든다.
		진동시간을 추적하며, 진동시간이 0이 되면 해당 모터 속도는 0으로 설정된다.
	*/
	void vibrateControllers(float frameTime);

};

#endif