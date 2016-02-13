// 2016. 2. 3.

#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"
#include "dx9_game_engine\input.h"
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
		SceneName _nextScene;
		Graphics* _graphics;
		Input* _input;
		TextureList* _textureList;
	public:
		Scene();
		virtual ~Scene();

		virtual void start(Graphics* graphics, Input* input, TextureList* textureList);
		virtual void update() = 0;
		virtual void lateUpdate() = 0;
		virtual void render() = 0;

		virtual void releaseAll() = 0;
		virtual void resetAll() = 0;

		virtual SceneName getNextScene();
	};
}

#endif