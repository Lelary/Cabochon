// 2016. 2. 3.
#ifndef _IN_GAME_SCENE_H
#define _IN_GAME_SCENE_H

#include "scene.h"
#include "steering_wheel_control.h"
#include "marble_generator.h"
#include "marble_control.h"
#include "dx9_game_engine\text_dx.h"

namespace scenes
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
		Image _gameOverLine;
		Image _gameOverMessage;
		Image _gameClearMessage;

		TextDX _debugText;
		TextDX _errorText;
		std::string _debugMessage;
		std::string _errorMessage;

		SteeringWheelControl _wheelControl;
		MarbleControl _marbleControl;

		bool shootMarble();
		void rotateWheel(float frameTime);
		void keyInPlayState(float frameTime);
		void updatePlayState(float frameTime);

	public:
		InGameScene(Graphics& graphics, Input& input, TextureList& textureList);
		virtual ~InGameScene();

		virtual void start();
		virtual void update(float frameTime);
		virtual void lateUpdate(float frameTime);
		virtual void render();

		virtual void releaseAll();
		virtual void resetAll();

		//-----------------
		BoardState getBoardState() const;
		SteeringWheelControl& getSteeringWheelControl();



	};
}
#endif
