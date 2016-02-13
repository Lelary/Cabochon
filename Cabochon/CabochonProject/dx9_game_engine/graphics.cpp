// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 3, Ch4, Ch5, Ch8

#include "graphics.h"

Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;

	// 폭 및 높이는 initialize()에서 바뀐다.
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
	
	//D3D Presentation Parameter 초기화.
	initD3Dpp();
	
	// 전체화면 일 때
	if (fullscreen)
	{
		// 어댑터가 호환된다면, 리프레시 속도를 호환 되는 것으로 설정 한다.
		if (isAdapterCompatible())
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR, "The graphics device does not support the specified resolution and/or format."));
	}

	// 그래픽 카드가 텍스처, 라이팅, 정점 셰이더를 지원하는지 확인한다.
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// 디바이스가 텍스처, 라이팅을 지원하지 않거나 정점 셰이더 1.1을 지원하지 않는다면 소프트웨어 정점 처리로 전환한다.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// Direct3D Divice 생성
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

	// 프리미티브의 알파 블렌딩을 위한 설정
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
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // desktop setting 사용.
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

// 로스트 상태가 된 디바이스를 확인한다.
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;
	result = device3d->TestCooperativeLevel();
	return result;
}

// 그래픽 디바이스를 리셋한다.
HRESULT Graphics::reset()
{
	result = E_FAIL;
	initD3Dpp(); // D3D Presentation Parameter를 초기화 한다.
	sprite->OnLostDevice();
	result = device3d->Reset(&d3dpp); // 그래픽 디바이스 리셋을 시도한다.
	// 프리미티브의 알파 블렌딩을 위한 설정
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


// 백 버퍼를 지우고 DirectX의 BegineScene()을 호출한다.
HRESULT Graphics::beginScene()
{
	result = E_FAIL;
	if (device3d == NULL)
		return result;

	device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0f, 0);
	result = device3d->BeginScene();
	return result;
}

// DirectX 의 EndScene()을 호출한다.
HRESULT Graphics::endScene()
{
	result = E_FAIL;
	if (device3d)
		result = device3d->EndScene();
	return result;
}

HRESULT Graphics::loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture)
{
	// 파일 정보를 읽기 위한 구조체.
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try {
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// 파일로 부터 폭과 높이를 얻는다.
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// 파일을 불러와 새 텍스처를 생성한다.
		result = D3DXCreateTextureFromFileEx(
			device3d,			// 3D 디바이스.
			filename,			// 이미지 파일명.
			info.Width,			// 텍스처 폭.
			info.Height,		// 텍스처 높이.
			1,					// 밉맵 수준. ( 연결하지 않을때는 1 사용, 2D -> 불필요 )
			0,					// 사용.
			D3DFMT_UNKNOWN,		// 표면 형식 (기본).
			D3DPOOL_DEFAULT,	// 텍스처를 위한 메모리 클래스.
			D3DX_DEFAULT,		// 이미지 필터.
			D3DX_DEFAULT,		// 밉 필터.
			transcolor,			// 투명도를 위한 색상 키.
			&info,				// 비트맵 파일 정보 ( 불러온 파일로부터 ).
			NULL,				// 색상 팔래트.
			&texture			// 텍스처 목적지.
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
	// 비트맵 파일 정보를 읽기 위한 구조체
	D3DXIMAGE_INFO info;
	result = E_FAIL;

	try{
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// 비트맵 파일로부터 폭과 높이를 가져온다.
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// 불러온 비트맵 이미지 파일로부터 새 텍스처를 생성한다.
		result = D3DXCreateTextureFromFileEx(
			device3d,			// 3d 디바이스
			filename,			// 비트맵 파일명
			info.Width,			// 비트맵 이미지 폭
			info.Height,		// 비트맵 이미지 높이
			1,					// 밉-맵 레벨(1은 체인 없음)
			0,					// 사용
			D3DFMT_UNKNOWN,		// 표면 형식(기본 값)
			D3DPOOL_SYSTEMMEM,	// 시스템은 락을 걸 수 없다.
			D3DX_DEFAULT,		// 이미지 필터
			D3DX_DEFAULT,		// 밉 필터
			transcolor,			// 투명도를 위한 색상 키
			&info,				// 비트맵 파일 정보(불러온 파일로부터)
			NULL,				// 색상 팔레트
			&texture);			// 텍스처 목적지
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

	// 정점 버퍼 생성
	result = device3d->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	if (FAILED(result))
		return result;
	void* ptr;

	// 데이터가 안으로 전송 되기 전에 버퍼에 Lock을 걸어야 한다.
	result = vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	if (FAILED(result))
		return result;
	// 정점 데이터를 버퍼에 복사한다.
	memcpy(ptr, verts, size);
	// 버퍼에 걸린 Lock을 해제한다.
	vertexBuffer->Unlock();
	return result;
}

bool Graphics::drawQuad(LP_VERTEXBUFFER vertexBuffer)
{
	HRESULT result = E_FAIL;
	if (vertexBuffer == NULL)
		return false;

	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, true);				// 알파 블렌딩 활성화
	device3d->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexC));
	device3d->SetFVF(D3DFVF_VERTEX);
	result = device3d->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);			// 알파 블렌딩 비활성화

	if (FAILED(result))
		return false;

	return true;
}