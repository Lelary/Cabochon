// 2016. 2. 3.
#ifndef _IN_GAME_SCENE_H
#define _IN_GAME_SCENE_H

#include "scene.h"
#include "steering_wheel_control.h"
#include "marble_generator.h"
#include "marble_control.h"
#include "dx9_game_engine\text_dx.h"

namespace frameworks
{
	using controls::SteeringWheelControl;
	using controls::MarbleControl;
	using controls::MarbleGenerator;
	using controls::BoardState;

	class InGameScene
		:public Scene
	{
	private:
		Image _backGround;
		TextDX _text;
		TextDX _text2;

		SteeringWheelControl _wheelControl;
		MarbleControl _marbleControl;

		BoardState getBoardState() const;
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
