// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.
// �ڵ��� �Ϻδ� å�� �������� �ʾ�, �ҽ��ڵ带 ���� ���۷������� �ٿ�޾� ������.

#include "input.h"

Input::Input()
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;

	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;

	newLine = true;
	textIn = "";
	charIn = 0;

	mouseX = 0;
	mouseY = 0;
	mouseRawX = 0;
	mouseRawY = 0;
	mouseLButton = false;
	mouseMButton = false;
	mouseRButton = false;
	mouseX1Button = false;
	mouseX2Button = false;
}

Input::~Input()
{
	if (mouseCaptured)
		ReleaseCapture();
}

/*
	���콺�� ��Ʈ�ѷ� �Է��� �ʱ�ȭ �Ѵ�. 
	���콺�� ĸó�ϸ� capture = true �� �����Ѵ�.
	GameError�� ������.
*/
void Input::initialize(HWND hwnd, bool capture)
{
	try {
		mouseCaptured = capture;
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
		if (mouseCaptured)
			SetCapture(hwnd);
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

/*
	���� : ���� Ű �ڵ� (0~255)�� �����ϰ� �ִ� wParam
*/
void Input::keyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;
		keysPressed[wParam] = true;
	}
}
/*
���� : ���� Ű �ڵ� (0~255)�� �����ϰ� �ִ� wParam
*/
void Input::keyUp(WPARAM wParam)
{

	if (wParam < inputNS::KEYS_ARRAY_LEN)
		keysDown[wParam] = false;
}

/*
textIn ���ڿ��� �Է��� ���ڸ� �����Ѵ�.
���� : ���ڸ� �����ϰ� �ִ� wParam
*/
void Input::keyIn(WPARAM wParam)
{
	if (newLine)
	{
		textIn.clear();
		newLine = false;
	}
	if (wParam == '\b')
	{
		if (textIn.length()>0)
			textIn.erase(textIn.size() - 1);
	}
	else
	{
		textIn += wParam;
		charIn = wParam;
	}
	if ((char) wParam == '\r')
		newLine = true;
}

bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

bool Input::anyKeyPressed()const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		if (keysPressed[i] == true)
			return true;
	return false;
}



void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}
void Input::clearTextIn()
{
	textIn.clear();
}
void Input::clearAll()
{
	clear(inputNS::KEYS_MOUSE_TEXT);
}

void Input::clear(UCHAR what)
{
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0;  i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	if (what&inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	if (what&inputNS::MOUSE)
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
	}
	if (what&inputNS::TEXT_IN)
		clearTextIn();
}

void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

/*
	ó�� ���� ���� ���콺 �����͸� �о� mouseRawX, mouseRawY�� �����Ѵ�.
	�̷� ��ƾ�� ������ ���콺�� ȣȯ�ȴ�.
*/
void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

void Input::setMouseXButton(WPARAM wParam) {
	mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
	mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
}