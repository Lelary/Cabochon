// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 5.

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

	// �ؽ�ó�� ����Ű�� �����͸� ��ȯ�Ѵ�.
	LP_TEXTURE getTexture() const { return texture; }
	// �ؽ�ó�� ���� ��ȯ�Ѵ�.
	UINT getWidth() const{ return width; }
	// �ؽ�ó�� ���̸� ��ȯ�Ѵ�.
	UINT getHeight() const { return height; }

	// ��ũ�κ��� �ؽ�ó ������ �ҷ��´�.
	bool initialize(Graphics* g, LPCTSTR f);
	// �׷��� ����̽��� �ν�Ʈ ������ �� ȣ��ȴ�.
	void onLostDevice();
	// �׷��� ����̽��� ���� ���� �� ȣ��ȴ�.
	void onResetDevice();
		
};
#endif