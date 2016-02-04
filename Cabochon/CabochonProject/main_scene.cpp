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

// 그래픽 디바이스가 로스트 상태가 됐을 떄 호출됨. 예약된 모든 비디오 메모리를 해제하고 그래픽 디바이스를 리셋한다.
// Texture의 onLostDevice() 호출.
void MainScene::releaseAll()
{

}

// 모든 표면을 재생성 하고 모든 개체를 리셋한다.
// Texture의 onResetDevice() 호출.
void MainScene::resetAll()
{

}