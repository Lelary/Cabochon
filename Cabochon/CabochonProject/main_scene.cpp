//2016. 2. 4

#include "main_scene.h"
using frameworks::MainScene;

void MainScene::start()
{
	if (started)
		return;


	//if (!shipTexture.initialize(graphics, SHIP_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//if (!ship.initialize(graphics, 0, 0, 0, &shipTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//planet.setX(GAME_WIDTH * 0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	//ship.setX(GAME_WIDTH / 4);
	//ship.setY(GAME_HEIGHT / 4);

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