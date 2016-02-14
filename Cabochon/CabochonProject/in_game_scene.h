// 2016. 2. 3.

#include "scene.h"

namespace frameworks
{
	class InGameScene
		:public Scene
	{
	private:
		Image _backGround;

	public:
		InGameScene(Graphics& graphics, Input& input, TextureList& textureList);
		virtual ~InGameScene();

		virtual void start();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();
	};
}
