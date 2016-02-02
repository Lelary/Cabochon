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
	// Ư�� Ű�� ���� ��� true�� �ȴ�.
	bool keysDown[inputNS::KEYS_ARRAY_LEN];
	// ���� ������ �����ϴ� ���� Ư�� Ű�� ������ �ִ� ��� true�� �ȴ�. 
	bool keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::string textIn;			// ����ڰ� �Է��� �ؽ�Ʈ.
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

	//��Ʈ�ѷ��� ����.
	ControllerState controllers[MAX_CONTROLLERS];

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
	std::string getTextIn(){ return textIn; }
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

	/*
		��Ʈ�ѷ� �Է� �޼ҵ�.
	*/
	void checkControllers();
	void readControllers();
	const ControllerState* getControllerState(UINT n);
	const WORD getGamepadButtons(UINT n);

	/*
		��Ʈ�ѷ� n �� D �е� ��ư�� ���¸� ��ȯ�ϴ� �Լ���.
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
		��Ʈ�ѷ� n��
		�Ƴ��α� ��Ʈ�ѷ��� Ʈ������ ���¸� ��ȯ�ϴ� �Լ���.
		0~255 ������ BYTE ���� ��ȯ�Ѵ�. 0�� �� ���¸� ǥ���ϰ�, 255�� ������ ���� ���¸� ǥ���Ѵ�.
		input.h ��ܿ� �������� ��õǾ� �ִ�.
	*/
	BYTE getGamepadLeftTrigger(UINT n);
	BYTE getGamepadRightTrigger(UINT n);

	/*
		��Ʈ�ѷ� n��
		�Ƴ��α� ��Ʈ���� �潺ƽ�� ���¸� ��ȯ�ϴ� �Լ���.
		SHORT ���� �潺ƽ�� ��ġ�� �˷��ִµ�, �� �࿡ ���� -32,768 ~ 32,768 �� ������ ǥ���ȴ�.
		0�� �߾��� �ǹ��Ѵ�. 
		input.h ��ܿ� �������� ��õǾ� �ִ�.
	*/
	SHORT getGamepadThumbLX(UINT n);
	SHORT getGamepadThumbLY(UINT n);
	SHORT getGamepadThumbRX(UINT n);
	SHORT getGamepadThumbRY(UINT n);

	/*
		��Ʈ�ѷ� n�� ���� ���͸� �����ϰ� �����. 
		������ ���� �������� ������ �����Ѵ�. 
		speed 0 = ������� ����. 65536 = 100%.
		sec = ������ �ʴ��� �ð�.
	*/
	void gamePadVibrateLeft(UINT n, WORD speed, float sec);
	/*
		��Ʈ�ѷ� n�� ������ ���͸� �����ϰ� �����.
		�������� ���� �������� ������ �����Ѵ�.
		speed 0 = ������� ����. 65536 = 100%.
		sec = ������ �ʴ��� �ð�.
	*/
	void gamePadVibrateRight(UINT n, WORD speed, float sec);

	/*
		����� ��Ʈ�ѷ��� �����ϰ� �����.
		�����ð��� �����ϸ�, �����ð��� 0�� �Ǹ� �ش� ���� �ӵ��� 0���� �����ȴ�.
	*/
	void vibrateControllers(float frameTime);

};

#endif