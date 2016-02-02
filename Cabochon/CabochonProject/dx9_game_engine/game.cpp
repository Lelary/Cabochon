// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 4.

#include "game.h"

Game::Game()
{
	input = new Input();
	// �߰� �ʱ�ȭ �۾��� input->initialize()�� ȣ���� �ڿ� ó���Ѵ�.
	paused = false;
	graphics = NULL;
	initialized = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

// ������ �޽��� �ڵ鷯.
LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:	case WM_SYSKEYDOWN:
			input->keyDown(wParam);
			return 0;
		case WM_KEYUP:	case WM_SYSKEYUP:
			input->keyUp(wParam);
			return 0;
		case WM_CHAR:
			input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE:
			input->mouseIn(lParam);
			return 0;
		case WM_INPUT:
			input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN:
			input->setMouseLButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:
			input->setMouseLButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONDOWN:
			input->setMouseMButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONUP:
			input->setMouseMButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONDOWN:
			input->setMouseRButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONUP:
			input->setMouseRButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			input->setMouseXButton(wParam);
			input->mouseIn(lParam);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Game::initialize(HWND hw)
{
	hwnd = hw;
	graphics = new Graphics();
	// GameError �� ������.
	graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
	
	// Input ��ü�� �ʱ�ȭ�Ѵ�. ���� ���콺�� ĸ������ �ʴ´�.
	input->initialize(hwnd, false);

	// ������ Ÿ�̸� ����� �õ��Ѵ�.
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));
	//���� �ð��� �����´�.
	QueryPerformanceCounter(&timeStart);
	initialized = true;
}

// �ν�Ʈ ���°� �� �׷��� ����̽��� ó���Ѵ�.
void Game::handleLostGraphicsDevice()
{
	// �ν�Ʈ ���°� �� ����̽��� �׽�Ʈ �ϰ� ó���Ѵ�.
	hr = graphics->getDeviceState();
	if (FAILED(hr))
	{
		// ����̽��� �ν�Ʈ �����̸� ������ �Ұ��� �ϴٸ�
		if (hr == D3DERR_DEVICELOST)
		{
			Sleep(100);
			return;
		}

		// ����̽��� �ν�Ʈ ���� ������ ������ ���� �ϴٸ�
		else if (hr == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			hr = graphics->reset();
			if (FAILED(hr))
				return;
			resetAll();
		}

		// �ٸ� ����̽� ����
		else
			return;
	}
}

void Game::renderGame()
{
	// ������ ����.
	if (SUCCEEDED(graphics->beginScene()))
	{
		// Derived class ���� ȣ��. (Pure Virtual Function).
		render();

		//������ ��.
		graphics->endScene();
	}
	handleLostGraphicsDevice();

	// ����� ǥ��.
	graphics->showBackBuffer();
}

void Game::run(HWND hwnd)
{
	if (graphics == NULL)
		return;

	// ������ ���������� ���� ����� �ð��� ����� frameTime�� �����Ѵ�.
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// ������ ���� �ڵ�. winmm.lib �ʿ�.
	// ����� �ð��� ���ϴ� ������ �ӵ��� �������� �ʴ´ٸ�
	if (frameTime < MIN_FRAME_TIME)
	{
		sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1); // 1ms �ػ� Ÿ�̸� ��û
		Sleep(sleepTime);
		timeEndPeriod(1); // 1ms �ػ� Ÿ�̸� ����
		return;
	}
	if (frameTime>0.0)
		fps = (fps*0.99f) + (0.01f / frameTime);
	// ������ �ӵ��� �ſ� �����ٸ� �ִ� frameTime���� ����.
	if (frameTime > MAX_FRAME_TIME)
		frameTime = MAX_FRAME_TIME;
	timeStart = timeEnd;
	input->readControllers();

	// �Ͻ� ���� ���°� �ƴ϶�� ����.
	if (!paused)
	{
		// Pure Virtual Functions.
		update();
		ai();
		collisions();
		input->vibrateControllers(frameTime);

	}
	renderGame();
	// ��� Ű Ȯ���� ���� �Ŀ� �Է��� �����.
	input->clear(inputNS::KEYS_PRESSED);
}

void Game::releaseAll()
{

}

void Game::resetAll()
{

}

void Game::deleteAll()
{
	releaseAll();			//��� Graphics item�� ���� onLostDevice()�� ȣ���Ѵ�.
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
	initialized = false;
}