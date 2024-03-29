// 2016. 2. 5
#include "texture_list.h"
using scenes::TextureList;

TextureList::TextureList()
	:_graphics(nullptr)
{
	_textureFiles[Title] = TEXT("images\\title.png");
	_textureFiles[MainMessage] = TEXT("images\\main_message.png");
	_textureFiles[GameOverMessage] = TEXT("images\\game_over_message.png");
	_textureFiles[GameClearMessage] = TEXT("images\\game_clear_message.png");
	_textureFiles[BulletinBoard] = TEXT("images\\bulletin_board.png");

#if defined(DEBUG) | defined(_DEBUG)
	_textureFiles[Marbles] = TEXT("images\\marbles_textures_lines.png");
#else
	_textureFiles[Marbles] = TEXT("images\\marbles_textures.png");
#endif
	_textureFiles[SteeringWheel] = TEXT("images\\steering_wheel.png");
	_textureFiles[GameOverLine] = TEXT("images\\game_over_line.png");
	_textureFiles[Ceiling] = TEXT("images\\ceiling.png");
	_textureFiles[BackGroundCity] = TEXT("images\\back_ground_city.png");
	_textureFiles[BackGroundMountain] = TEXT("images\\back_ground_mountain.png");
	
}
TextureList::~TextureList()
{
	onLostDevice();
}
Graphics* TextureList::getGraphics()
{
	return _graphics;
}

void TextureList::setGraphics(Graphics& graphics)
{
	_graphics = &graphics;
}
void TextureList::loadTextures()
{
	if (_graphics == nullptr)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture."));

	for (int i = 0; i < Num; i++)
		if (!_textures[i].initialize(_graphics, _textureFiles[i].c_str()))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture "+std::to_string(i)));

	for (int i = 0; i < Num; i++)
		if (_textures[i].getTexture() == NULL)
			throw(GameError(gameErrorNS::FATAL_ERROR, "There is un-loaded Texture"));
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
