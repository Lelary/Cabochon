// 2016. 2. 11.

#include "console.h"

Console::Console()
{
	initialized = false;
	graphics = NULL;
	visible = false;
	fontColor = consoleNS::FONT_COLOR;
	backColor = consoleNS::BACK_COLOR;

	x = consoleNS::X;
	y = consoleNS::Y;

	textRect.bottom = consoleNS::Y + consoleNS::HEIGHT - consoleNS::MARGIN;
	textRect.left = consoleNS::X + consoleNS::MARGIN;
	textRect.right = consoleNS::X + consoleNS::WIDTH - consoleNS::MARGIN;
	textRect.top = consoleNS::Y + consoleNS::MARGIN;

	vertexBuffer = NULL;

	rows = 0;
	scrollAmount = 0;
}

Console::~Console()
{
	onLostDevice();
}

bool Console::initialize(Graphics* g, Input* in)
{
	// 그래픽 시스템.
	try{
		graphics = g;
		input = in;

		// 왼쪽 상단.
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// 오른쪽 상단.
		vtx[1].x = x + consoleNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// 오른쪽 하단.
		vtx[2].x = x + consoleNS::WIDTH;
		vtx[2].y = y + consoleNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// 왼쪽 하단.
		vtx[3].x = x;
		vtx[3].y = y + consoleNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		graphics->createVertexBuffer(vtx, sizeof(vtx), vertexBuffer);

		// directX 글꼴 초기화.
		if (dxFont.initialize(graphics, consoleNS::FONT_HEIGHT, false, false, consoleNS::FONT) == false)
			return false;
		dxFont.setFontColor(fontColor);
	}
	catch (...)
	{
		return false;
	}
	initialized = true;
	return true;
}

const void Console::draw()
{
	if (!visible || graphics == NULL || !initialized)
		return;
	// 배경 그리기.
	graphics->drawQuad(vertexBuffer);
	if (text.size() == 0)
		return;
	// 스프라이트 그리기 시작.
	graphics->spriteBegin();

	textRect.left = 0;
	textRect.top = 0;
	// textRect의 하단을 한 행의 높이로 설정한다.
	dxFont.print(TEXT("|"), textRect, DT_CALCRECT);	// "I" 는 전체 높이 캐릭터로 사용된다.
	int rowHeight = textRect.bottom + 2;		// 한 행의 높이 (+2 는 행 간격이다.)
	if (rowHeight <= 0)							// true가 되면 안되므로 가능한 결과로 강제한다.
		rowHeight = 20;

	rows = (consoleNS::HEIGHT - 2 * consoleNS::MARGIN) / rowHeight;
	rows -= 2;									// 하단에 입력 프롬프트를 위한 공간.
	if (rows <= 0)								// true가 되면 안되므로 가능한 결과로 강제한다.
		rows = 5;

	// 텍스트 한 행을 표시할 사각형을 설정한다.
	textRect.left = (long)(x + consoleNS::MARGIN);
	textRect.right = (long)(textRect.right + consoleNS::WIDTH - consoleNS::MARGIN);
	// -2 * rowHeight는 입력 프롬프트를 위한 공간이다.
	textRect.bottom = (long)(y + consoleNS::HEIGHT - 2 * consoleNS::MARGIN - 2 * rowHeight);

	// 상단부터 하단까지 모든 행에 대해서 (최대 text.size())
	for (int r = scrollAmount; r < rows + scrollAmount && r < (int)(text.size()); r++)
	{
		// 해당 행에 대해 텍스트를 표시하는 사각형의 top을 설정한다.
		textRect.top = textRect.bottom - rowHeight;
		// 텍스트 한 행을 표시한다.
		dxFont.print(text[r], textRect, DT_LEFT);
		// 텍스트를 표시하는 사각형의 bottom을 조정한다.
		textRect.bottom -= rowHeight;
	}
	// 명령 프롬프트와 현재 명령을 표시한다.
	// 프롬프트 텍스트를 표시하는 사각형을 설정한다.
	textRect.bottom = (long)(y + consoleNS::HEIGHT - consoleNS::MARGIN);
	textRect.top = textRect.bottom - rowHeight;
	std::wstring prompt = TEXT(">");					// 프롬프트 문자열 구축.
	prompt += input->getTextIn();
	dxFont.print(prompt, textRect, DT_LEFT);	// 프롬프트와 명령 표시.

	// 스프라이트 그리기 끝.
	graphics->spriteEnd();
}

void Console::showHide()
{
	if (!initialized)
		return;

	visible = !visible;
	input->clear(inputNS::KEYS_PRESSED | inputNS::TEXT_IN);	// 이전의 입력을 지운다.
}

void Console::print(const std::wstring& str)
{
	if (!initialized)
		return;
	text.push_front(str);						// str을 text deque에 추가한다.
	if (text.size() > consoleNS::MAX_LINES)
		text.pop_back();						// 가장 오래된 줄을 삭제한다.
}

std::wstring Console::getCommand()
{
	if (!initialized | !visible)
		return TEXT("");

	if (input->wasKeyPressed(CONSOLE_KEY))
		hide();

	if (input->wasKeyPressed(ESC_KEY))
		return TEXT("");

	if (input->wasKeyPressed(VK_UP))
		scrollAmount++;
	else if (input->wasKeyPressed(VK_DOWN))
		scrollAmount--;
	else if (input->wasKeyPressed(VK_PRIOR))
		scrollAmount += rows;
	else if (input->wasKeyPressed(VK_NEXT))
		scrollAmount -= rows;
	if (scrollAmount < 0)
		scrollAmount = 0;
	if (scrollAmount>consoleNS::MAX_LINES - 1)
		scrollAmount = consoleNS::MAX_LINES - 1;
	if (scrollAmount > (int)(text.size()) - 1)
		scrollAmount = (int)(text.size()) - 1;
	
	// 사용자가 입력한 텍스트를 가져온다.
	commandStr = input->getTextIn();
	// 게임을 통해 키를 전달하면 안된다.
	input->clear(inputNS::KEYS_DOWN | inputNS::KEYS_PRESSED | inputNS::MOUSE);
	
	if (commandStr.length() == 0)						// 명령이 입력되지 않았다면
		return TEXT("");
	if (commandStr.at(commandStr.length() - 1) != '\r')	// Enter키를 누르지 않았다면
		return TEXT("");
	commandStr.erase(commandStr.length() - 1);
	input->clearTextIn();								// 입력 줄을 지운다.
	return commandStr;									// 명령을 반환한다.
}

void Console::onLostDevice()
{
	if (!initialized)
		return;
	dxFont.onLostDevice();
	SAFE_RELEASE(vertexBuffer);
}

void Console::onResetDevice()
{
	if (!initialized)
		return;
	graphics->createVertexBuffer(vtx, sizeof(vtx), vertexBuffer);
	dxFont.onResetDevice();
}