// 2016. 2. 10.

#include "text_dx.h"

TextDX::TextDX()
{
	color = SETCOLOR_ARGB(255, 255, 255, 255);

	fontRect.top = 0;
	fontRect.left = 0;
	fontRect.right = GAME_WIDTH;
	fontRect.bottom = GAME_HEIGHT;
	dxFont = NULL;
	angle = 0;
}

TextDX::~TextDX()
{
	SAFE_RELEASE(dxFont);
}

bool TextDX::initialize(Graphics* g, int height, bool bold, bool italic, const std::wstring& fontName)
{
	graphics = g;
	UINT weight = FW_NORMAL;
	if (bold)
		weight = FW_BOLD;

	// DirectX �۲� ����.
	if (FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(), &dxFont)))
		return false;

	// ��ȯ ����� �ʱ�ȭ �Ѵ�.
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

	return true;
}

int TextDX::print(const std::wstring& str, int x, int y)
{
	if (dxFont == NULL)
		return 0;
	// �۲��� ��ġ�� �����Ѵ�.
	fontRect.top = y;
	fontRect.left = x;
	// ȸ�� �߽�.
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);
	// ������ ���� �ؽ�Ʈ�� ȸ���ϴ� ����� �����Ѵ�.
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);
	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_LEFT, color);
}

int TextDX::print(const std::wstring& str, RECT& rect, UINT format)
{
	if (dxFont == NULL)
		return 0;
	// �ؽ�Ʈ�� ȸ������ �ʰ� ����� �����Ѵ�.
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, NULL, NULL);
	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &rect, format, color);
}

void TextDX::onLostDevice()
{
	if (dxFont == NULL)
		return;
	dxFont->OnLostDevice();
}

void TextDX::onResetDevice()
{
	if (dxFont == NULL)
		return;
	dxFont->OnResetDevice();
}