// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class MainScene
		:public Scene
	{
	private:
		Image startButton;
		Image exitButton;

	public:
		MainScene();
		virtual ~MainScene();


		virtual void start(Graphics* graphics, Input* input, TextureList* textureList);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	};
}