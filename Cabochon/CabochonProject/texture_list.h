// 2016. 2. 4.

#ifndef _TEXTURE_LIST_H
#define _TEXTURE_LIST_H

#include "dx9_game_engine\texture_manager.h"
#include "frameworks.h"
#include <array>

namespace frameworks
{
	class TextureList
	{
	public:
		//enum TextureName { None = -1, Buttons = 0, Marbles, SteeringWheel, Num };

		enum TextureName { None = -1, StartButton = 0, ExitButton, Num };

	private:
		const char* START_BUTTON_IMAGE = "images\\start_button.png";
		const char* EXIT_BUTTON_IMAGE = "images\\exit_button.png";

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