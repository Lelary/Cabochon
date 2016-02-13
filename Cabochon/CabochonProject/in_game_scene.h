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

		virtual void start(Graphics* graphics, Input* input, TextureList* textureList);
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();
	};
}
