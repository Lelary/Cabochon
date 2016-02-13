// 2016. 2. 5
#include "texture_list.h"
using frameworks::TextureList;

TextureList::TextureList()
{

}
TextureList::~TextureList()
{
	onLostDevice();
}

void TextureList::loadTextures(Graphics* graphics)
{
	if (!_textures[StartButton].initialize(graphics, START_BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture"));

	if (!_textures[ExitButton].initialize(graphics, EXIT_BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture"));

	if (!_textures[Marble].initialize(graphics, MARBLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture"));

	for (int i = 0; i < Num; i++)
	{
		if (_textures[i].getTexture() == NULL)
			throw(GameError(gameErrorNS::FATAL_ERROR, "There is un-loaded Texture"));
	}
}

TextureManager* TextureList::getTexture(TextureName num)
{
	if (num <= None || num >= Num)
		throw GameError(gameErrorNS::FATAL_ERROR, "invailed TextureName");

	return &_textures[num];
}

void TextureList::onLostDevice()
{
	for (unsigned int i = 0; i < _textures.size(); i++)
		_textures[i].onLostDevice();
}

void TextureList::onResetDevice()
{
	for (unsigned int i = 0; i < _textures.size(); i++)
		_textures[i].onResetDevice();
}
