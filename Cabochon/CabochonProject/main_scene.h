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
		MainScene()
			:Scene() {}

		virtual void start(Graphics* graphics, std::vector<TextureManager>* textures);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	};
}