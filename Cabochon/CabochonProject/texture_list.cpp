// 2016. 2. 5
#include "texture_list.h"
using scenes::TextureList;

TextureList::TextureList()
	:_graphics(nullptr)
{
	_textureFiles[StartButton] = "images\\start_button.png";
	_textureFiles[ExitButton] = "images\\exit_button.png";
	_textureFiles[Marbles] = "images\\marbles_textures_lines.png";
	_textureFiles[SteeringWheel] = "images\\steering_wheel.png";
	_textureFiles[SteeringWheel] = "images\\steering_wheel.png";
	_textureFiles[BackGroundCity] = "images\\back_ground_city.png";
	_textureFiles[BackGroundMountain] = "images\\back_ground_mountain.png";
	
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
