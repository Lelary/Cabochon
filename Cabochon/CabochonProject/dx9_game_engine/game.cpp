// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 4.

#include "game.h"

Game::Game()
{
	input = new Input();
	// 추가 초기화 작업은 input->initialize()를 호출한 뒤에 처리한다.
	paused = false;
	graphics = NULL;
	console = NULL;
	fps = 100;
	fpsOn = false;
	initialized = false;
}

Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

// 윈도우 메시지 핸들러.
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
	// GameError 를 던진다.
	graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
	
	// Input 객체를 초기화한다. 또한 마우스를 캡쳐하지 않는다.
	input->initialize(hwnd, false);

	// 콘솔을 초기화 한다.
	console = new Console();
	console->initialize(graphics, input);
	console->print("---Console---");

	// DirectX 글꼴 초기화
	if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	dxFont.setFontColor(gameNS::FONT_COLOR);

	// 고성능의 타이머 사용을 시도한다.
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));
	//시작 시간을 가져온다.
	QueryPerformanceCounter(&timeStart);
	initialized = true;
}

// 로스트 상태가 된 그래픽 디바이스를 처리한다.
void Game::handleLostGraphicsDevice()
{
	// 로스트 상태가 된 디바이스를 테스트 하고 처리한다.
	hr = graphics->getDeviceState();
	if (FAILED(hr))
	{
		// 디바이스가 로스트 상태이며 리셋이 불가능 하다면
		if (hr == D3DERR_DEVICELOST)
		{
			Sleep(100);
			return;
		}

		// 디바이스가 로스트 상태 이지만 리셋이 가능 하다면
		else if (hr == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			hr = graphics->reset();
			if (FAILED(hr))
				return;
			resetAll();
		}

		// 다른 디바이스 에러
		else
			return;
	}
}

void Game::renderGame()
{
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];

	if (SUCCEEDED(graphics->beginScene()))	// 렌더링 시작.
	{
		// Derived class 에서 호출. (Pure Virtual Function).
		render();

		graphics->spriteBegin();			// 스프라이트 그리기 시작.
		if (fpsOn)
		{
			// fps를 C string 으로 변환한다.
			_snprintf_s(buffer, BUF_SIZE, "fps %d ", (int)fps);
			dxFont.print(buffer, GAME_WIDTH - 100, GAME_HEIGHT - 28);
		}
		
		graphics->spriteEnd();				// 스프라이트 그리기 끝.
		console->draw();					// 콘솔이 그려지고 게임의 상단에 나타난다.

		graphics->endScene();				//렌더링 끝.
	}
	handleLostGraphicsDevice();

	graphics->showBackBuffer();				// 백버퍼 표시.
}

void Game::run(HWND hwnd)
{
	if (graphics == NULL)
		return;

	// 마지막 프레임으로 부터 경과된 시간을 계산해 frameTime에 저장한다.
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// 절전을 위한 코드. winmm.lib 필요.
	// 경과된 시간이 원하는 프레임 속도에 충족하지 않는다면
	if (frameTime < MIN_FRAME_TIME)
	{
		sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1); // 1ms 해상도 타이머 요청
		Sleep(sleepTime);
		timeEndPeriod(1); // 1ms 해상도 타이머 종료
		return;
	}
	if (frameTime>0.0)
		fps = (fps*0.99f) + (0.01f / frameTime);
	// 프레임 속도가 매우 느리다면 최대 frameTime으로 제한.
	if (frameTime > MAX_FRAME_TIME)
		frameTime = MAX_FRAME_TIME;
	timeStart = timeEnd;

	// 일시 중지 상태가 아니라면 갱신.
	if (!paused)
	{
		// Pure Virtual Functions.
		update();
		ai();
		collisions();

	}
	renderGame();

	// 콘솔 키를 확인 한다.
	if (input->wasKeyPressed(CONSOLE_KEY))
	{
		console->showHide();
		// 콘솔이 보인다면 게임을 일시정지 한다.
		paused = console->getVisible();
	}
	// 사용자가 입력한 콘솔 명령을 처리한다.
	consoleCommand();
	
	// 모든 키 확인이 끝난 후에 입력을 지운다.
	input->clear(inputNS::KEYS_PRESSED);
}

/*
	콘솔 명령을 처리한다.
	새 콘솔 명령이 추가 되면 상속받은 클래스에서 이 함수를 오버라이딩 한다.
*/
void Game::consoleCommand()
{
	// 콘솔로부터 명령을 얻는다.
	command = console->getCommand();
	if (command == "")
		return;
	if (command == "help")
	{
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		return;
	}

	if (command == "fps")
	{
		fpsOn = !fpsOn;
		if (fpsOn)
			console->print("fps On");
		else
			console->print("fps Off");
	}
}

void Game::releaseAll()
{
	SAFE_ON_LOST_DEVICE(console);
	dxFont.onLostDevice();
	return;
}

void Game::resetAll()
{
	dxFont.onResetDevice();
	SAFE_ON_RESET_DEVICE(console);
	return;
}

void Game::deleteAll()
{
	releaseAll();			//모든 Graphics item에 대해 onLostDevice()를 호출한다.
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
	SAFE_DELETE(console);
	initialized = false;
}