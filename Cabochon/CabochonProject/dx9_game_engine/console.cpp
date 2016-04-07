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
	// �׷��� �ý���.
	try{
		graphics = g;
		input = in;

		// ���� ���.
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// ������ ���.
		vtx[1].x = x + consoleNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// ������ �ϴ�.
		vtx[2].x = x + consoleNS::WIDTH;
		vtx[2].y = y + consoleNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// ���� �ϴ�.
		vtx[3].x = x;
		vtx[3].y = y + consoleNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		graphics->createVertexBuffer(vtx, sizeof(vtx), vertexBuffer);

		// directX �۲� �ʱ�ȭ.
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
	// ��� �׸���.
	graphics->drawQuad(vertexBuffer);
	if (text.size() == 0)
		return;
	// ��������Ʈ �׸��� ����.
	graphics->spriteBegin();

	textRect.left = 0;
	textRect.top = 0;
	// textRect�� �ϴ��� �� ���� ���̷� �����Ѵ�.
	dxFont.print(TEXT("|"), textRect, DT_CALCRECT);	// "I" �� ��ü ���� ĳ���ͷ� ���ȴ�.
	int rowHeight = textRect.bottom + 2;		// �� ���� ���� (+2 �� �� �����̴�.)
	if (rowHeight <= 0)							// true�� �Ǹ� �ȵǹǷ� ������ ����� �����Ѵ�.
		rowHeight = 20;

	rows = (consoleNS::HEIGHT - 2 * consoleNS::MARGIN) / rowHeight;
	rows -= 2;									// �ϴܿ� �Է� ������Ʈ�� ���� ����.
	if (rows <= 0)								// true�� �Ǹ� �ȵǹǷ� ������ ����� �����Ѵ�.
		rows = 5;

	// �ؽ�Ʈ �� ���� ǥ���� �簢���� �����Ѵ�.
	textRect.left = (long)(x + consoleNS::MARGIN);
	textRect.right = (long)(textRect.right + consoleNS::WIDTH - consoleNS::MARGIN);
	// -2 * rowHeight�� �Է� ������Ʈ�� ���� �����̴�.
	textRect.bottom = (long)(y + consoleNS::HEIGHT - 2 * consoleNS::MARGIN - 2 * rowHeight);

	// ��ܺ��� �ϴܱ��� ��� �࿡ ���ؼ� (�ִ� text.size())
	for (int r = scrollAmount; r < rows + scrollAmount && r < (int)(text.size()); r++)
	{
		// �ش� �࿡ ���� �ؽ�Ʈ�� ǥ���ϴ� �簢���� top�� �����Ѵ�.
		textRect.top = textRect.bottom - rowHeight;
		// �ؽ�Ʈ �� ���� ǥ���Ѵ�.
		dxFont.print(text[r], textRect, DT_LEFT);
		// �ؽ�Ʈ�� ǥ���ϴ� �簢���� bottom�� �����Ѵ�.
		textRect.bottom -= rowHeight;
	}
	// ��� ������Ʈ�� ���� ����� ǥ���Ѵ�.
	// ������Ʈ �ؽ�Ʈ�� ǥ���ϴ� �簢���� �����Ѵ�.
	textRect.bottom = (long)(y + consoleNS::HEIGHT - consoleNS::MARGIN);
	textRect.top = textRect.bottom - rowHeight;
	std::wstring prompt = TEXT(">");					// ������Ʈ ���ڿ� ����.
	prompt += input->getTextIn();
	dxFont.print(prompt, textRect, DT_LEFT);	// ������Ʈ�� ��� ǥ��.

	// ��������Ʈ �׸��� ��.
	graphics->spriteEnd();
}

void Console::showHide()
{
	if (!initialized)
		return;

	visible = !visible;
	input->clear(inputNS::KEYS_PRESSED | inputNS::TEXT_IN);	// ������ �Է��� �����.
}

void Console::print(const std::wstring& str)
{
	if (!initialized)
		return;
	text.push_front(str);						// str�� text deque�� �߰��Ѵ�.
	if (text.size() > consoleNS::MAX_LINES)
		text.pop_back();						// ���� ������ ���� �����Ѵ�.
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
	
	// ����ڰ� �Է��� �ؽ�Ʈ�� �����´�.
	commandStr = input->getTextIn();
	// ������ ���� Ű�� �����ϸ� �ȵȴ�.
	input->clear(inputNS::KEYS_DOWN | inputNS::KEYS_PRESSED | inputNS::MOUSE);
	
	if (commandStr.length() == 0)						// ����� �Էµ��� �ʾҴٸ�
		return TEXT("");
	if (commandStr.at(commandStr.length() - 1) != '\r')	// EnterŰ�� ������ �ʾҴٸ�
		return TEXT("");
	commandStr.erase(commandStr.length() - 1);
	input->clearTextIn();								// �Է� ���� �����.
	return commandStr;									// ����� ��ȯ�Ѵ�.
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