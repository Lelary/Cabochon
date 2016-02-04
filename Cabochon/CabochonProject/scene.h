// 2016. 2. 3.

#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"

/*
	2016. 2. 2.
	dx9_game_engine 의 Game class와 
	controls 과의 연결고리.
*/
namespace frameworks
{
	enum class SceneName { Null = -1, MainScene = 0, InGameScene, Num };

	class Scene
	{
	protected:
		//start 함수가 실행 되었었으면 true;
		bool started;
	public:
		Scene():started(false){}

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void lateUpdate() = 0;
		virtual void render() = 0;

		// 그래픽 디바이스가 로스트 상태가 됐을 떄 호출됨. 예약된 모든 비디오 메모리를 해제하고 그래픽 디바이스를 리셋한다.
		// Texture의 onLostDevice() 호출.
		virtual void releaseAll() = 0;

		// 모든 표면을 재생성 하고 모든 개체를 리셋한다.
		// Texture의 onResetDevice() 호출.
		virtual void resetAll() = 0;
	};
}

#endif