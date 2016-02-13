// 2016. 2. 3.

#include "scene.h"
#include "dx9_game_engine\text_dx.h"

namespace frameworks
{
	class MainScene
		:public Scene
	{
	private:
		Image startButton;
		Image exitButton;

		TextDX text;

	public:
		MainScene();
		virtual ~MainScene();

		virtual void start(Graphics* graphics, Input* input, TextureList* textureList);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();

	};
}