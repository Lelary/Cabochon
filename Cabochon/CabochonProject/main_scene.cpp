//2016. 2. 4

#include "main_scene.h"
using frameworks::MainScene;

void MainScene::start()
{
	if (started)
		return;



	started = true;
}
void MainScene::update()
{

}
void MainScene::lateUpdate()
{

}
void MainScene::render()
{

}

// �׷��� ����̽��� �ν�Ʈ ���°� ���� �� ȣ���. ����� ��� ���� �޸𸮸� �����ϰ� �׷��� ����̽��� �����Ѵ�.
// Texture�� onLostDevice() ȣ��.
void MainScene::releaseAll()
{

}

// ��� ǥ���� ����� �ϰ� ��� ��ü�� �����Ѵ�.
// Texture�� onResetDevice() ȣ��.
void MainScene::resetAll()
{

}