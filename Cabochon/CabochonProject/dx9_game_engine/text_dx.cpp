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

	// DirectX 글꼴 생성.
	if (FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(), &dxFont)))
		return false;

	// 변환 행렬을 초기화 한다.
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

	return true;
}

int TextDX::print(const std::wstring& str, int x, int y)
{
	if (dxFont == NULL)
		return 0;
	// 글꼴의 위치를 설정한다.
	fontRect.top = y;
	fontRect.left = x;
	// 회전 중심.
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);
	// 각도에 따라 텍스트를 회전하는 행렬을 설정한다.
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);
	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_LEFT, color);
}

int TextDX::print(const std::wstring& str, RECT& rect, UINT format)
{
	if (dxFont == NULL)
		return 0;
	// 텍스트가 회전하지 않게 행렬을 설정한다.
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