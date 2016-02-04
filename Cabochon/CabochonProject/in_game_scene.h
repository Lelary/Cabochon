// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class InGameScene
		:public Scene
	{
	private:


	public:
		InGameScene() :Scene(){}

		virtual void start(Graphics* graphics, std::vector<TextureManager>* textures);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	};
}