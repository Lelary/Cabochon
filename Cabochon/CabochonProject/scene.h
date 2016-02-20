// 2016. 2. 3.

#ifndef _SCENE_H
#define _SCENE_H

#include "scenes.h"
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
namespace scenes
{
	enum class SceneName { None = -1, MainScene = 0, InGameScene, Num };

	class Scene
	{
	protected:
		//start 함수가 실행 되었었으면 true;
		bool _started;
		SceneName _nextScene;
		Graphics& _graphics;
		Input& _input;
		TextureList& _textureList;
	public:
		Scene(Graphics& graphics, Input& input, TextureList& textureList);
		virtual ~Scene();

		virtual void start();
		virtual void update(float frameTime) = 0;
		virtual void lateUpdate(float frameTime) = 0;
		virtual void render() = 0;

		virtual void releaseAll() = 0;
		virtual void resetAll() = 0;

		virtual SceneName getNextScene();
	};
}

#endif