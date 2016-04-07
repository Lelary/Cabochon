// 2016. 2. 4.

#ifndef _TEXTURE_LIST_H
#define _TEXTURE_LIST_H

#include "dx9_game_engine\texture_manager.h"
#include "scenes.h"
#include <array>
#include <string>

namespace scenes
{
	class TextureList
	{
	public:
		enum TextureName { 
			None = -1,
			Title = 0,
			MainMessage,
			GameOverMessage, 
			GameClearMessage,
			BulletinBoard,
			Marbles, 
			SteeringWheel,
			GameOverLine,
			Ceiling,
			BackGroundCity, 
			BackGroundMountain, 
			Num };

	private:
		Graphics* _graphics;
		std::wstring _textureFiles[TextureName::Num];
		std::array<TextureManager, Num> _textures;

	public:
		TextureList();
		virtual ~TextureList();

		void loadTextures();

		Graphics* getGraphics();
		void setGraphics(Graphics& graphics);

		TextureManager* getTexture(TextureName num);
		void onLostDevice();
		void onResetDevice();

	};
}

#endif