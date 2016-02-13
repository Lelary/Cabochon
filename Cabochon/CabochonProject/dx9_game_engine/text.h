// 2016. 2. 10.

#ifndef _TEXT_H
#define _TEXT_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "image.h"
#include "constants.h"

namespace textNS
{
	enum Alignment{LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM};
	struct FontData
	{
		UINT left;
		UINT right;
	};

	const int FONT_BORDER = 3;								// 각 문자의 경계선 크기. ( 1px의 투명 테두리 * 2 + 눈에보이는격자 )
	const int FONT_WIDTH = 48;								// 문자의 픽셀 단위 너비.
	const int FONT_HEIGHT = 62;								// 문자의 픽셀 단위 높이.
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;		// 각 문자 격자의 픽셀 단위 폭.
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;		// 각 문자 격자의 픽셀 단위 높이.
	const int COLUMNS = 16;									// 글꼴 이미지의 열 수.
	const int ROWS = 14;									// 글꼴 이미지의 행 수.
	const int FRAME = 1;									// 각 이미지에 대한 애니메이션의 프레임 수.
	const double ANIM_DELAY = 0.0;							// 애니메이션 프레임 지연 시간.
	const int MAX_FONT_HEIGHT = 1000;						// 글꼴의 최대 높이.
	const int MIN_CHAR = 0x0020;							// 왼쪽 상단 문자의 문자 코드. 일반적으로 비어있다고 가정. (0x20 = 32)
	const int MAX_CHAR = 0x00ff;							// 오른쪽 하단 문자의 문자 코드. (0xff = 255)
	const int PROPORTIONAL_SPACING = 5;						// 1:1 크기에서 비례 간격이 있는 문자 사이의 픽셀 단위 간격.
	const int TAB_SIZE = 8;									// 문자 위치로 표현 되는 탭 간격의 크기.
	const char UNDERLINE = '_';								// 밑줄을 표시하는 데 사용하는 문자. 
	const char SOLID = 0x7f;								// Solid Block을 표시하는데 사용되는 문자.
	const int BOLD_SIZE = 4;								/* 굵은 체 출력은 문자 사이에 수평 간격을 갖는 문자를 각각 두번 출력해 수행.
															1:1 크기의 문자에 적용되는 오프셋의 픽셀 수. */
}

class Text : public Image
{
private:
	TextureManager fontTexture;
	LP_TEXTURE textureData;
	char* file;
	Graphics* graphics;
	UINT width, height;
	textNS::FontData fontData[textNS::ROWS][textNS::COLUMNS];
	COLOR_ARGB color;
	COLOR_ARGB backColor;
	UINT fontHeight;
	UINT tabSize;
	UINT proportionalSpacing;
	bool proportional;
	bool underline;
	bool bold;
	textNS::Alignment align;

public:
	Text();
	virtual ~Text();

	/*
		텍스트를 초기화 한다.
		글꼴 이미지에서 각 문자의 왼쪽, 오른쪽 모서리를 찾는다.
		Post : fontData 배열은 각 문자의 왼쪽과 오른쪽 모서리를 포함한다.
	*/
	virtual bool initialize(Graphics* g, const char* file);
	virtual void update(float frameTime){};
	virtual void onLostDevice();
	virtual void onResetDevice();

	virtual void setXY(int x, int y);
	virtual void print(const std::string& str);
	/*
		X, Y 위치에 문자열을 출력한다.
		Pre : spriteBegin()
		Post : spriteEnd()
	*/
	virtual void print(const std::string& str, int x, int y);
	virtual void print(const std::string& str, int x, int y, textNS::Alignment align);
	/*
		현재 글꼴의 크기에 따라 문자열의 픽셀 단위 폭과 높이를 결정한다.
		문자열을 표시하지 않는다.
	*/
	virtual void getWidthHeight(const std::string& str, UINT& width, UINT& height);
	virtual void setFontColor(COLOR_ARGB c) { color = c; }
	virtual COLOR_ARGB getFontColor() { return color; }
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }
	virtual COLOR_ARGB getBackColor() { return backColor; }
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > textNS::MAX_FONT_HEIGHT)
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)textNS::FONT_HEIGHT;
	}
	virtual UINT getFontHeight() {
		return fontHeight;
	}
	virtual void setProportional(bool p){ proportional = p; }
	virtual bool getProportional(){ return proportional; }
	virtual void setProportionalSpacing(UINT s){ proportionalSpacing = s; }
	virtual UINT getProportionalSPacing(){ return proportionalSpacing; }
	virtual void setUnderline(bool u){ underline = u; }
	virtual bool getUnderline(){ return underline; }
	virtual void setBold(bool b){ bold = b; }
	virtual bool getBold(){ return bold; }
	virtual void setTabSize(UINT size){
		if (size == 0)
			return;
		tabSize = size;
	}
	virtual UINT getTabSize(){ return tabSize; }
	/*
		spriteData.x, spriteData.y 를 현재 문자열 및 정렬에 맞게 설정한다.
		기본 정렬은 LEFT 이다.
	*/
	virtual void doAlign(const std::string& str);
	/*
		색상과 채우기를 사용해 spriteData에 있는 문자 스프라이트를 표시한다.
		밑줄과 굵은체를 사용한다.
	*/
	virtual void drawChar(UCHAR ch);
};


#endif