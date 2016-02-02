#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "game_error.h"

// DirectX 포인터 형식.
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define LP_STRITE LPD3DXSPRITE

// 색상 정의.
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// 일부 색상
	// 0 ~ 255 범위의 ARGB 숫자로 이루어져 있다.
	// A = 알파 채널 (투명도, 255는 불투명함을 의미한다.)
	// R = 빨간색, G = 초록색, B = 파란색.
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);			// colorFilter를 명시해서 그랠 때 사용한다.
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);	// 25% alpha 컬러를 얻을 때 AND
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);	// 50% alpha 컬러를 얻을 때 AND
	const COLOR_ARGB BACK_COLOR = NAVY;								// background color of game

	enum DISPLAY_MODE{ TOGGLE, FULLSCREEN, WINDOW };
}

// Graphics::drawSprite 에서 스프라이트를 그리기 위해 필요한 속성.
struct SpriteData
{
	int width;		// 스프라이트의 픽셀 단위 폭.
	int height;		// 스프라이트의 픽셀 단위 높이.
	float x;		// 화면 위치 (스프라이트의 왼쪽 상단 모서리).
	float y;		// 화면 위치 (스프라이트의 왼쪽 상단 모서리).
	float scale;	// < 1 이면 작게, > 1 이면 크게.
	float angle;	// 라디안 단위.
	RECT rect;		// 큰 이미지에서 사용할 이미지 선택.
	LP_TEXTURE texture;	// 텍스처를 가리키는 포인터.
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics
{
private:
	// DirectX 관련 변수.
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	LP_STRITE sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// Windows 관련 변수.
	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	COLOR_ARGB backColor;

	/*
		private method
		엔진 내부에서만 사용하는 함수. 안에 사용자가 서비스 할 수 있는 부분은 없다.
		D3D 프레젠테이션 매개 변수를 초기화 한다.
	*/
	void initD3Dpp();

public:
	Graphics();
	virtual ~Graphics();
	// 동적 할당된 direct3d 와 device3d 를 해제한다.
	void releaseAll();

	/*
		DirectX 그래픽을 초기화 한다.
		hw = 윈도우의 핸들
		width = 픽셀 단위 폭
		height = 픽셀 단위 높이
		full = true면 전체 화면, false면 창 화면
		에러가 발생할 경우 GameError를 던진다.
	*/
	void initialize(HWND hw, int width, int height, bool full);

	// 화면에 보이지 않는 Back Buffer를 화면에 표시한다.
	HRESULT showBackBuffer();

	/*
	어댑터가 d3dpp 에 지정된 백 버퍼의 높이, 폭, 리프레시 속도 (Refresh Rate)와 호환되는지 확인한다.
	찾았다면 pMode 구조체에 호환 모드의 형식을 채운다.
	이전 : d3dpp가 초기화 됐다.
	이후 : 호환되는 모드를 찾았고 pMode 구조체가 채워져 있다면 true를 반환한다.
	호환되는 모드를 찾지 못하면 false를 반환한다.
	*/
	bool isAdapterCompatible();

	HRESULT reset();

	LP_3D   get3D()             { return direct3d; }
	LP_3DDEVICE get3Ddevice()   { return device3d; }
	HDC     getDC()             { return GetDC(hwnd); }
	HRESULT getDeviceState();

	void setBackColor(COLOR_ARGB c) { backColor = c; }

	HRESULT beginScene();
	HRESULT endScene();
	void spriteBegin();
	void spriteEnd();

	/*
		텍스처를 기본 D3D 메모리로 불러 온다. (일반적인 텍스처 사용).
		엔진 내부에서만 사용한다.
		게임 텍스처를 불러오기 위해 TextureManager 클래스를 사용한다.
		Pre :	filename 은 텍스처 파일의 이름이다.
				transcolor은 투명색이다.
		Post :	width와 height = 텍스처의 크기.
				texture는 텍스처를 가리키는 포인터이다.
		HRESULT를 반환한다.
	*/
	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture);
	void drawSprite(const SpriteData& spriteData, COLOR_ARGB color = graphicsNS::WHITE);
};

#endif