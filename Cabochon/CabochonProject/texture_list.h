// 2016. 2. 4.

#ifndef _TEXTURE_LIST_H
#define _TEXTURE_LIST_H

#include "dx9_game_engine\texture_manager.h"
#include "frameworks.h"
#include <array>
#include <string>

namespace frameworks
{
	class TextureList
	{
	public:
		enum TextureName { None = -1, StartButton = 0, ExitButton, Marbles, SteeringWheel, BackGroundCity, BackGroundMountain, Num };

	private:
		std::string _textureFiles[TextureName::Num];
		std::array<TextureManager, Num> _textures;

	public:
		TextureList();
		virtual ~TextureList();

		void loadTextures(Graphics* graphics);

		TextureManager* getTexture(TextureName num);
		void onLostDevice();
		void onResetDevice();

	};
}

#endif