// 2016. 2. 3.
#ifndef _IN_GAME_SCENE_H
#define _IN_GAME_SCENE_H

#include "scene.h"
#include "steering_wheel_control.h"
#include "marble_generator.h"
#include "marble_control.h"

namespace frameworks
{
	using controls::SteeringWheelControl;
	using controls::MarbleControl;
	using controls::MarbleGenerator;

	class InGameScene
		:public Scene
	{
	private:
		Image _backGround;

		SteeringWheelControl _wheelControl;
		MarbleControl _marbleControl;

	public:
		InGameScene(Graphics& graphics, Input& input, TextureList& textureList);
		virtual ~InGameScene();

		virtual void start();
		virtual void update(float frameTime);
		virtual void lateUpdate(float frameTime);
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();

	};
}
#endif
