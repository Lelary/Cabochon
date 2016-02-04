// 2016. 2. 3.

#ifndef _SCENE_H
#define _SCENE_H

#include "frameworks.h"
#include "dx9_game_engine\texture_manager.h"
#include "dx9_game_engine\image.h"

/*
	2016. 2. 2.
	dx9_game_engine �� Game class�� 
	controls ���� �����.
*/
namespace frameworks
{
	enum class SceneName { Null = -1, MainScene = 0, InGameScene, Num };

	class Scene
	{
	protected:
		//start �Լ��� ���� �Ǿ������� true;
		bool started;
	public:
		Scene():started(false){}

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void lateUpdate() = 0;
		virtual void render() = 0;

		// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
		// Texture�� onLostDevice() ȣ��.
		virtual void releaseAll() = 0;

		// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
		// Texture�� onResetDevice() ȣ��.
		virtual void resetAll() = 0;
	};
}

#endif