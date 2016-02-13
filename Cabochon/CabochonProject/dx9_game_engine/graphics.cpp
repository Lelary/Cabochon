// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 3, Ch4, Ch5, Ch8

#include "graphics.h"

Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;

	// �� �� ���̴� initialize()���� �ٲ��.
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
	backColor = SETCOLOR_ARGB(255, 0, 0, 128); // dark blue
}

Graphics::~Graphics()
{
	releaseAll();
}

void Graphics::releaseAll()
{
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	// Create Direct3D
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));
	
	//D3D Presentation Parameter �ʱ�ȭ.
	initD3Dpp();
	
	// ��üȭ�� �� ��
	if (fullscreen)
	{
		// ����Ͱ� ȣȯ�ȴٸ�, �������� �ӵ��� ȣȯ �Ǵ� ������ ���� �Ѵ�.
		if (isAdapterCompatible())
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR, "The graphics device does not support the specified resolution and/or format."));
	}

	// �׷��� ī�尡 �ؽ�ó, ������, ���� ���̴��� �����ϴ��� Ȯ���Ѵ�.
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// ����̽��� �ؽ�ó, �������� �������� �ʰų� ���� ���̴� 1.1�� �������� �ʴ´ٸ� ����Ʈ���� ���� ó���� ��ȯ�Ѵ�.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// Direct3D Divice ����
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd, 
		behavior, 
		&d3dpp, 
		&device3d);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3d device"));

	result = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(result))
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite"));

	// ������Ƽ���� ���� ������ ���� ����
	device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void Graphics::initD3Dpp()
{
	try{
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; // 24bit color
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // desktop setting ���.
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing D3D presentation parameters"));
	}
}

HRESULT Graphics::showBackBuffer()
{
	result = E_FAIL;
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

// �ν�Ʈ ���°� �� ����̽��� Ȯ���Ѵ�.
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;
	result = device3d->TestCooperativeLevel();
	return result;
}

// �׷��� ����̽��� �����Ѵ�.
HRESULT Graphics::reset()
{
	result = E_FAIL;
	initD3Dpp(); // D3D Presentation Parameter�� �ʱ�ȭ �Ѵ�.
	sprite->OnLostDevice();
	result = device3d->Reset(&d3dpp); // �׷��� ����̽� ������ �õ��Ѵ�.
	// ������Ƽ���� ���� ������ ���� ����
	device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	sprite->OnResetDevice();
	return result;
}

bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat);

	for (UINT i = 0; i < modes; i++)
	{
		result = direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat, i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}


// �� ���۸� ����� DirectX�� BegineScene()�� ȣ���Ѵ�.
HRESULT Graphics::beginScene()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;

	device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0f, 0);
	result = device3d->BeginScene();
	return result;
}

// DirectX �� EndScene()�� ȣ���Ѵ�.
HRESULT Graphics::endScene()
{
	result = E_FAIL;
	if (device3d)
		result = device3d->EndScene();
	return result;
}

HRESULT Graphics::loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture)
{
	// ���� ������ �б� ���� ����ü.
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try {
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// ���Ϸ� ���� ���� ���̸� ��´�.
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// ������ �ҷ��� �� �ؽ�ó�� �����Ѵ�.
		result = D3DXCreateTextureFromFileEx(
			device3d,			// 3D ����̽�.
			filename,			// �̹��� ���ϸ�.
			info.Width,			// �ؽ�ó ��.
			info.Height,		// �ؽ�ó ����.
			1,					// �Ӹ� ����. ( �������� �������� 1 ���, 2D -> ���ʿ� )
			0,					// ���.
			D3DFMT_UNKNOWN,		// ǥ�� ���� (�⺻).
			D3DPOOL_DEFAULT,	// �ؽ�ó�� ���� �޸� Ŭ����.
			D3DX_DEFAULT,		// �̹��� ����.
			D3DX_DEFAULT,		// �� ����.
			transcolor,			// ������ ���� ���� Ű.
			&info,				// ��Ʈ�� ���� ���� ( �ҷ��� ���Ϸκ��� ).
			NULL,				// ���� �ȷ�Ʈ.
			&texture			// �ؽ�ó ������.
		);

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
	}

	return result;
}

HRESULT Graphics::loadTextureSystemMem(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture)
{
	// ��Ʈ�� ���� ������ �б� ���� ����ü
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try{
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// ��Ʈ�� ���Ϸκ��� ���� ���̸� �����´�.
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// �ҷ��� ��Ʈ�� �̹��� ���Ϸκ��� �� �ؽ�ó�� �����Ѵ�.
		result = D3DXCreateTextureFromFileEx(
			device3d,			// 3d ����̽�
			filename,			// ��Ʈ�� ���ϸ�
			info.Width,			// ��Ʈ�� �̹��� ��
			info.Height,		// ��Ʈ�� �̹��� ����
			1,					// ��-�� ����(1�� ü�� ����)
			0,					// ���
			D3DFMT_UNKNOWN,		// ǥ�� ����(�⺻ ��)
			D3DPOOL_SYSTEMMEM,	// �ý����� ���� �� �� ����.
			D3DX_DEFAULT,		// �̹��� ����
			D3DX_DEFAULT,		// �� ����
			transcolor,			// ������ ���� ���� Ű
			&info,				// ��Ʈ�� ���� ����(�ҷ��� ���Ϸκ���)
			NULL,				// ���� �ȷ�Ʈ
			&texture);			// �ؽ�ó ������
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics;;loadTexture"));
	}
	return result;
}

void Graphics::drawSprite(const SpriteData& spriteData, COLOR_ARGB color)
{
	if (spriteData.texture == NULL)
		return;

	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(	(float)spriteData.width / 2 * spriteData.scale ,
											(float)spriteData.height / 2 * spriteData.scale);

	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x,
										(float)spriteData.y);

	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);

	if (spriteData.flipHorizontal)
	{
		scaling.x *= -1;
		spriteCenter.x -= (float)(spriteData.width*spriteData.scale);
		translate.x += (float)(spriteData.width*spriteData.scale);
	}

	if (spriteData.flipVertical)
	{
		scaling.y *= -1;
		spriteCenter.y -= (float)(spriteData.height*spriteData.scale);
		translate.y += (float)(spriteData.height*spriteData.scale);
	}

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, (float)(spriteData.angle), &translate);
	sprite->SetTransform(&matrix);
	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);
}

void Graphics::spriteBegin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Graphics::spriteEnd()
{
	sprite->End();
}

HRESULT Graphics::createVertexBuffer(VertexC verts[], UINT size, LP_VERTEXBUFFER& vertexBuffer)
{
	HRESULT result = E_FAIL;

	// ���� ���� ����
	result = device3d->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	if (FAILED(result))
		return result;
	void* ptr;

	// �����Ͱ� ������ ���� �Ǳ� ���� ���ۿ� Lock�� �ɾ�� �Ѵ�.
	result = vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	if (FAILED(result))
		return result;
	// ���� �����͸� ���ۿ� �����Ѵ�.
	memcpy(ptr, verts, size);
	// ���ۿ� �ɸ� Lock�� �����Ѵ�.
	vertexBuffer->Unlock();
	return result;
}

bool Graphics::drawQuad(LP_VERTEXBUFFER vertexBuffer)
{
	HRESULT result = E_FAIL;
	if (vertexBuffer == NULL)
		return false;

	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// ���� ���� Ȱ��ȭ
	device3d->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexC));
	device3d->SetFVF(D3DFVF_VERTEX);
	result = device3d->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);			// ���� ���� ��Ȱ��ȭ

	if (FAILED(result))
		return false;

	return true;
}