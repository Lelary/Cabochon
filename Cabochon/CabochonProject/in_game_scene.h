// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class InGameScene
		:public Scene
	{
	private:


	public:
		InGameScene() 
			:Scene() {}
		virtual ~InGameScene(){}

		virtual void start(Graphics* graphics, TextureList* textureList);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	};
}
