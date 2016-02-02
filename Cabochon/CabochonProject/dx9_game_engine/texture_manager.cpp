// 2016. 1. 31.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 5.

#include "texture_manager.h"

TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;
}

TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}

bool TextureManager::initialize(Graphics* g, const char* f)
{
	try {
		graphics = g;
		file = f;
		hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
		if (FAILED(hr))
		{
			SAFE_RELEASE(texture);
			return false;
		}
	}
	catch (...) { return false; }
	initialized = true;
	return true;
}
void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(texture);
}
void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}