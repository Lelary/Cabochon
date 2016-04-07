// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 5.

#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
private:
	UINT width;
	UINT height;
	LP_TEXTURE texture;
	LPCTSTR file;
	Graphics* graphics;
	bool initialized;
	HRESULT hr;

public:
	TextureManager();
	virtual ~TextureManager();

	// 텍스처를 가리키는 포인터를 반환한다.
	LP_TEXTURE getTexture() const { return texture; }
	// 텍스처의 폭을 반환한다.
	UINT getWidth() const{ return width; }
	// 텍스처의 높이를 반환한다.
	UINT getHeight() const { return height; }

	// 디스크로부터 텍스처 파일을 불러온다.
	bool initialize(Graphics* g, LPCTSTR f);
	// 그래픽 디바이스가 로스트 상태일 때 호출된다.
	void onLostDevice();
	// 그래픽 디바이스가 리셋 됐을 때 호출된다.
	void onResetDevice();
		
};
#endif