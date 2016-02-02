// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 4.
// 코드의 일부는 책에 나와있지 않아, 소스코드를 위의 레퍼런스에서 다운받아 복사함.

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
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;
	}
}

Input::~Input()
{
	if (mouseCaptured)
		ReleaseCapture();
}

/*
	마우스와 컨트롤러 입력을 초기화 한다. 
	마우스를 캡처하면 capture = true 로 설정한다.
	GameError를 던진다.
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
		ZeroMemory(controllers, sizeof(ControllerState)*MAX_CONTROLLERS);
		checkControllers();
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

/*
	이전 : 가상 키 코드 (0~255)를 포함하고 있는 wParam
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
이전 : 가상 키 코드 (0~255)를 포함하고 있는 wParam
*/
void Input::keyUp(WPARAM wParam)
{

	if (wParam < inputNS::KEYS_ARRAY_LEN)
		keysDown[wParam] = false;
}

/*
textIn 문자열에 입력한 문자를 저장한다.
이전 : 문자를 포함하고 있는 wParam
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
	처리 되지 않은 마우스 데이터를 읽어 mouseRawX, mouseRawY에 저장한다.
	이런 루틴은 고정밀 마우스와 호환된다.
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

void Input::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i <MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &controllers[i].state);
		if (result == ERROR_SUCCESS)
			controllers[i].connected = true;
		else
			controllers[i].connected = false;
	}
}

void Input::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)
				controllers[i].connected = false;
		}
	}
}
const ControllerState* Input::getControllerState(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return &controllers[n];
}
const WORD Input::getGamepadButtons(UINT n)
{
	if (n > MAX_CONTROLLERS)
		n = MAX_CONTROLLERS;
	return controllers[n].state.Gamepad.wButtons;
}


// Return state of controller n D-pad Up
bool Input::getGamepadDPadUp(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);
}

// Return state of controller n D-pad Down.
bool Input::getGamepadDPadDown(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
}

// Return state of controller n D-pad Left.
bool Input::getGamepadDPadLeft(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
}

// Return state of controller n D-pad Right.
bool Input::getGamepadDPadRight(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
}

// Return state of controller n Start button.
bool Input::getGamepadStart(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
}

// Return state of controller n Back button.
bool Input::getGamepadBack(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
}

// Return state of controller n Left Thumb button.
bool Input::getGamepadLeftThumb(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
}

// Return state of controller n Right Thumb button.
bool Input::getGamepadRightThumb(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
}

// Return state of controller n Left Shoulder button.
bool Input::getGamepadLeftShoulder(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
}

// Return state of controller n Right Shoulder button.
bool Input::getGamepadRightShoulder(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
}

// Return state of controller n A button.
bool Input::getGamepadA(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
}

// Return state of controller n B button.
bool Input::getGamepadB(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
}

// Return state of controller n X button.
bool Input::getGamepadX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
}

// Return state of controller n Y button.
bool Input::getGamepadY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
}

// Return value of controller n Left Trigger.
BYTE Input::getGamepadLeftTrigger(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.bLeftTrigger);
}

// Return value of controller n Right Trigger.
BYTE Input::getGamepadRightTrigger(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.bRightTrigger);
}

// Return value of controller n Left Thumbstick X.
SHORT Input::getGamepadThumbLX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.sThumbLX);
}

// Return value of controller n Left Thumbstick Y.
SHORT Input::getGamepadThumbLY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.sThumbLY);
}

// Return value of controller n Right Thumbstick X.
SHORT Input::getGamepadThumbRX(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.sThumbRX);
}

// Return value of controller n Right Thumbstick Y.
SHORT Input::getGamepadThumbRY(UINT n)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	return (controllers[n].state.Gamepad.sThumbRY);
}

void Input::gamePadVibrateLeft(UINT n, WORD speed, float sec)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	controllers[n].vibration.wLeftMotorSpeed = speed;
	controllers[n].vibrateTimeLeft = sec;
}

void Input::gamePadVibrateRight(UINT n, WORD speed, float sec)
{
	if (n > MAX_CONTROLLERS - 1)
		n = MAX_CONTROLLERS - 1;
	controllers[n].vibration.wRightMotorSpeed = speed;
	controllers[n].vibrateTimeRight = sec;
}
void Input::vibrateControllers(float frameTime)
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			controllers[i].vibrateTimeLeft -= frameTime;
			if (controllers[i].vibrateTimeLeft < 0)
			{
				controllers[i].vibrateTimeLeft = 0;
				controllers[i].vibration.wLeftMotorSpeed = 0;
			}

			controllers[i].vibrateTimeRight -= frameTime;
			if (controllers[i].vibrateTimeRight < 0)
			{
				controllers[i].vibrateTimeRight = 0;
				controllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &controllers[i].vibration);
		}
	}
}
