// 2016. 2. 10.

#ifndef _TEXT_DX_H
#define _TEXT_DX_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "constants.h"
#include "graphics.h"

class TextDX
{
private:
	Graphics* graphics;
	COLOR_ARGB color;
	LP_DXFONT dxFont;
	RECT fontRect;
	D3DXMATRIX matrix;
	float angle;

public:
	TextDX();
	virtual ~TextDX();

	// DirectX 글꼴 생성.
	virtual bool initialize(Graphics* g, int height, bool bold, bool italic, const std::string& fontName);
	
	/*
		x, y 위치에 텍스트를 출력한다.
		실패할 경우 0을, 성공할 경우 텍스트의 높이를 반환한다.
		Pre : spriteBegin()
		Post : spriteEnd()
	*/
	virtual int print(const std::string& str, int x, int y);
	/*
		DirectX 텍스트 서식을 사용해 RECT 안에 텍스트를 출력한다.
		실패할 경우 0을, 성공할 경우 텍스트의 높이를 반환한다.
		Pre : spriteBegin()
		Post : spriteEnd()
	*/
	virtual int print(const std::string& str, RECT& rect, UINT format);

	virtual float getDegrees(){ return angle*(180.0f / (float)PI); }
	virtual float getRadians() { return angle; }
	virtual COLOR_ARGB getFontColor(){ return color; }
	virtual void setDegrees(float deg){ angle = deg*((float)PI / 180.0f); }
	virtual void setRadians(float rad){ angle = rad; }
	virtual void setFontColor(COLOR_ARGB c){ color = c; }
	virtual void onLostDevice();
	virtual void onResetDevice();
};

#endif