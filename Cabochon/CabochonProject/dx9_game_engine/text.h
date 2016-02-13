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

	const int FONT_BORDER = 3;								// �� ������ ��輱 ũ��. ( 1px�� ���� �׵θ� * 2 + �������̴°��� )
	const int FONT_WIDTH = 48;								// ������ �ȼ� ���� �ʺ�.
	const int FONT_HEIGHT = 62;								// ������ �ȼ� ���� ����.
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;		// �� ���� ������ �ȼ� ���� ��.
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;		// �� ���� ������ �ȼ� ���� ����.
	const int COLUMNS = 16;									// �۲� �̹����� �� ��.
	const int ROWS = 14;									// �۲� �̹����� �� ��.
	const int FRAME = 1;									// �� �̹����� ���� �ִϸ��̼��� ������ ��.
	const double ANIM_DELAY = 0.0;							// �ִϸ��̼� ������ ���� �ð�.
	const int MAX_FONT_HEIGHT = 1000;						// �۲��� �ִ� ����.
	const int MIN_CHAR = 0x0020;							// ���� ��� ������ ���� �ڵ�. �Ϲ������� ����ִٰ� ����. (0x20 = 32)
	const int MAX_CHAR = 0x00ff;							// ������ �ϴ� ������ ���� �ڵ�. (0xff = 255)
	const int PROPORTIONAL_SPACING = 5;						// 1:1 ũ�⿡�� ��� ������ �ִ� ���� ������ �ȼ� ���� ����.
	const int TAB_SIZE = 8;									// ���� ��ġ�� ǥ�� �Ǵ� �� ������ ũ��.
	const char UNDERLINE = '_';								// ������ ǥ���ϴ� �� ����ϴ� ����. 
	const char SOLID = 0x7f;								// Solid Block�� ǥ���ϴµ� ���Ǵ� ����.
	const int BOLD_SIZE = 4;								/* ���� ü ����� ���� ���̿� ���� ������ ���� ���ڸ� ���� �ι� ����� ����.
															1:1 ũ���� ���ڿ� ����Ǵ� �������� �ȼ� ��. */
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
		�ؽ�Ʈ�� �ʱ�ȭ �Ѵ�.
		�۲� �̹������� �� ������ ����, ������ �𼭸��� ã�´�.
		Post : fontData �迭�� �� ������ ���ʰ� ������ �𼭸��� �����Ѵ�.
	*/
	virtual bool initialize(Graphics* g, const char* file);
	virtual void update(float frameTime){};
	virtual void onLostDevice();
	virtual void onResetDevice();

	virtual void setXY(int x, int y);
	virtual void print(const std::string& str);
	/*
		X, Y ��ġ�� ���ڿ��� ����Ѵ�.
		Pre : spriteBegin()
		Post : spriteEnd()
	*/
	virtual void print(const std::string& str, int x, int y);
	virtual void print(const std::string& str, int x, int y, textNS::Alignment align);
	/*
		���� �۲��� ũ�⿡ ���� ���ڿ��� �ȼ� ���� ���� ���̸� �����Ѵ�.
		���ڿ��� ǥ������ �ʴ´�.
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
		spriteData.x, spriteData.y �� ���� ���ڿ� �� ���Ŀ� �°� �����Ѵ�.
		�⺻ ������ LEFT �̴�.
	*/
	virtual void doAlign(const std::string& str);
	/*
		����� ä��⸦ ����� spriteData�� �ִ� ���� ��������Ʈ�� ǥ���Ѵ�.
		���ٰ� ����ü�� ����Ѵ�.
	*/
	virtual void drawChar(UCHAR ch);
};


#endif