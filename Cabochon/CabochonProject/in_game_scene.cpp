//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;

void InGameScene::start()
{
	if (started)
		return;




	started = true;
}
void InGameScene::update()
{

}
void InGameScene::lateUpdate()
{

}
void InGameScene::render()
{

}

// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
// Texture�� onLostDevice() ȣ��.
void InGameScene::releaseAll()
{

}

// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
// Texture�� onResetDevice() ȣ��.
void InGameScene::resetAll()
{

}