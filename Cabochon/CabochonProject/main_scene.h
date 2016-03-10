// 2016. 2. 3.
#ifndef _MAIN_SCENE_H
#define _MAIN_SCENE_H

#include "scene.h"
#include "dx9_game_engine\text_dx.h"

namespace scenes
{
	class MainScene
		:public Scene
	{
	private:
		Image _title;
		Image _mainMessage;

		TextDX _text;
	public:
		MainScene(Graphics& graphics, Input& input, TextureList& textureList);
		virtual ~MainScene();

		virtual void start();
		virtual void update(float frameTime);
		virtual void lateUpdate(float frameTime);
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();

	};
}
#endif