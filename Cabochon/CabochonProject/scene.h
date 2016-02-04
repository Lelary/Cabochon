// 2016. 2. 3.

#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"
#include <vector>
#include "dx9_game_engine\game_error.h"
#include "texture_list.h"
/*
	2016. 2. 2.
	dx9_game_engine 의 Game class와 
	controls 과의 연결고리.
*/
namespace frameworks
{
	enum class SceneName { Null = -1, MainScene = 0, InGameScene, Num };

	class Scene
	{
	protected:
		//start 함수가 실행 되었었으면 true;
		bool _started;
		Graphics* _graphics;
		std::vector<TextureManager>* _textures;

	public:
		Scene()
			:_started(false), _graphics(nullptr), _textures(nullptr){}

		virtual void start(Graphics* graphics, std::vector<TextureManager>* textures)
		{
			if (graphics != nullptr)
				_graphics = graphics;
			else
				throw(GameError(gameErrorNS::FATAL_ERROR, "nullptr!"));
			if (textures != nullptr)
				_textures = textures;
			else
				throw(GameError(gameErrorNS::FATAL_ERROR, "nullptr!"));
		}
		virtual void update() = 0;
		virtual void lateUpdate() = 0;
		virtual void render() = 0;
	};
}

#endif