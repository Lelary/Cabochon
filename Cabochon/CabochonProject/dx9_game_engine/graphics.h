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

// DirectX ������ ����.
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_SPRITE LPD3DXSPRITE
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D LPDIRECT3D9
#define LP_VERTEXBUFFER LPDIRECT3DVERTEXBUFFER9
#define LP_DXFONT   LPD3DXFONT

// ���� ����.
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// �Ϻ� ����
	// 0 ~ 255 ������ ARGB ���ڷ� �̷���� �ִ�.
	// A = ���� ä�� (����, 255�� ���������� �ǹ��Ѵ�.)
	// R = ������, G = �ʷϻ�, B = �Ķ���.
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
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);			// colorFilter�� ����ؼ� �׷� �� ����Ѵ�.
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);	// 25% alpha �÷��� ���� �� AND
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);	// 50% alpha �÷��� ���� �� AND
	const COLOR_ARGB BACK_COLOR = NAVY;								// background color of game

	enum DISPLAY_MODE{ TOGGLE, FULLSCREEN, WINDOW };
}

// ���� �ִ� ����
struct VertexC
{
	float x, y, z;
	float rhw;				// reciprocal homogeneous W ( set to 1 )
	unsigned long color;
};

// Flexible Vertex Format 
// D3DFVF_XYZRHW = ��ȯ�� �Ϸ�� ����.
// D3DFVF_DIFFUSE = diffuse �÷��� ���� ����.
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)


// Graphics::drawSprite ���� ��������Ʈ�� �׸��� ���� �ʿ��� �Ӽ�.
struct SpriteData
{
	int width;		// ��������Ʈ�� �ȼ� ���� ��.
	int height;		// ��������Ʈ�� �ȼ� ���� ����.
	float x;		// ȭ�� ��ġ (��������Ʈ�� ���� ��� �𼭸�).
	float y;		// ȭ�� ��ġ (��������Ʈ�� ���� ��� �𼭸�).
	float scale;	// < 1 �̸� �۰�, > 1 �̸� ũ��.
	float angle;	// ���� ����.
	RECT rect;		// ū �̹������� ����� �̹��� ����.
	LP_TEXTURE texture;	// �ؽ�ó�� ����Ű�� ������.
	bool flipHorizontal;
	bool flipVertical;
};

class Graphics
{
private:
	// DirectX ���� ����.
	LP_3D direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// Windows ���� ����.
	HRESULT result;
	HWND hwnd;
	bool fullscreen;
	int width;
	int height;
	COLOR_ARGB backColor;

	/*
		private method
		���� ���ο����� ����ϴ� �Լ�. �ȿ� ����ڰ� ���� �� �� �ִ� �κ��� ����.
		D3D ���������̼� �Ű� ������ �ʱ�ȭ �Ѵ�.
	*/
	void initD3Dpp();

public:
	Graphics();
	virtual ~Graphics();
	// ���� �Ҵ�� direct3d �� device3d �� �����Ѵ�.
	void releaseAll();

	/*
		DirectX �׷����� �ʱ�ȭ �Ѵ�.
		hw = �������� �ڵ�
		width = �ȼ� ���� ��
		height = �ȼ� ���� ����
		full = true�� ��ü ȭ��, false�� â ȭ��
		������ �߻��� ��� GameError�� ������.
	*/
	void initialize(HWND hw, int width, int height, bool full);

	// ȭ�鿡 ������ �ʴ� Back Buffer�� ȭ�鿡 ǥ���Ѵ�.
	HRESULT showBackBuffer();

	/*
	����Ͱ� d3dpp �� ������ �� ������ ����, ��, �������� �ӵ� (Refresh Rate)�� ȣȯ�Ǵ��� Ȯ���Ѵ�.
	ã�Ҵٸ� pMode ����ü�� ȣȯ ����� ������ ä���.
	���� : d3dpp�� �ʱ�ȭ �ƴ�.
	���� : ȣȯ�Ǵ� ��带 ã�Ұ� pMode ����ü�� ä���� �ִٸ� true�� ��ȯ�Ѵ�.
	ȣȯ�Ǵ� ��带 ã�� ���ϸ� false�� ��ȯ�Ѵ�.
	*/
	bool isAdapterCompatible();

	HRESULT reset();

	LP_3D   get3D()             { return direct3d; }
	LP_3DDEVICE get3Ddevice()   { return device3d; }
	HDC     getDC()             { return GetDC(hwnd); }
	LP_SPRITE   getSprite()     { return sprite; }
	HRESULT getDeviceState();

	void setBackColor(COLOR_ARGB c) { backColor = c; }

	HRESULT beginScene();
	HRESULT endScene();
	void spriteBegin();
	void spriteEnd();
	
	/*
		���� ���۸� ���� �Ѵ�.
		Pre :	verts[]�� ���� ���۸� �����Ѵ�.
				size = verts[]�� ũ��.
		Post :	������ ��� &vertexBuffer�� ���۸� ����Ų��.
	*/
	HRESULT createVertexBuffer(VertexC verts[], UINT size, LP_VERTEXBUFFER& vertexBuffer);
	
	/*
		�ﰢ�� ���� ����� ���� ������ ������ ���带 ǥ���Ѵ�.
		Pre :	createVertexBuffer�� �ð� ���� ������ ���带 �����ϴ� 
				�� ������ ������ vertexBuffer�� �����ϱ� ���� ���ƴ�.
				g3ddev->BeginScene�� ȣ�� �ƴ�.
		Post :	���尡 �׷�����.
	*/
	bool drawQuad(LP_VERTEXBUFFER vertexBuffer);

	/*
		�ؽ�ó�� �⺻ D3D �޸𸮷� �ҷ� �´�. (�Ϲ����� �ؽ�ó ���).
		���� ���ο����� ����Ѵ�.
		���� �ؽ�ó�� �ҷ����� ���� TextureManager Ŭ������ ����Ѵ�.
		Pre :	filename �� �ؽ�ó ������ �̸��̴�.
				transcolor�� ������̴�.
		Post :	width�� height = �ؽ�ó�� ũ��.
				texture�� �ؽ�ó�� ����Ű�� �������̴�.
		HRESULT�� ��ȯ�Ѵ�.
	*/
	HRESULT loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture);
	void drawSprite(const SpriteData& spriteData, COLOR_ARGB color = graphicsNS::WHITE);

	/*
		�ؽ�ó�� �ý��� �޸𸮿� �ҷ� �´�. (�ý��� �޸𸮴� ���� �� �� �ִ�.).
		�ȼ� �����Ϳ� �������� ������ �����Ѵ�.
		TextureManager Ŭ������ ����� ǥ�ø� ���� �ؽ�ó�� �ҷ� �´�.
		Pre:	filename �� �ؽ�ó ���ϸ��̴�.
				transcolor�� ���� ���̴�.
		Post:	width �� height = �ؽ�ó�� ũ��
				texture�� �ؽ�ó�� ����Ű�� �����ʹ�.
		HRESULT �� ��ȯ �ϰ� TextureData ����ü�� ä���.
	*/
	HRESULT loadTextureSystemMem(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture);
	
};

#endif