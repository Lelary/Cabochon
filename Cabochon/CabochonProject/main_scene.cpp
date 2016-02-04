//2016. 2. 4

#include "main_scene.h"
using frameworks::MainScene;

void MainScene::start()
{
	if (started)
		return;

	if (!startButtonTexture.initialize(graphics, START_BUTTON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Texture"));

	if (!startButton.initialize(graphics, 0, 0, 0, &startButtonTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	startButton.setX(GAME_WIDTH / 2);
	startButton.setY(GAME_HEIGHT * (3/4));

	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

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