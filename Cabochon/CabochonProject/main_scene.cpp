//2016. 2. 4

#include "main_scene.h"
using frameworks::MainScene;
using frameworks::TextureList;

MainScene::MainScene()
	:Scene()
{
	
}
MainScene::~MainScene()
{
	releaseAll();
}
void MainScene::start(Graphics* graphics, Input* input, TextureList* textureList)
{
	if (_started)
		return;

	Scene::start(graphics, input, textureList);
	
	if (!startButton.initialize(_graphics, 0, 0, 0, _textureList->getTexture(TextureList::TextureName::StartButton)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	startButton.setX(GAME_WIDTH / 2 - (startButton.getWidth()/2.0f));
	startButton.setY(GAME_HEIGHT*(1.0f / 2.0f));
	startButton.setScale(1);



	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

	_started = true;
}
void MainScene::update()
{
	if (_input->isKeyDown(ENTER_KEY))
	{
		_nextScene = SceneName::InGameScene;
	}
}
void MainScene::lateUpdate()
{

}
void MainScene::render()
{
	startButton.draw();
}

void MainScene::releaseAll()
{

}

void MainScene::resetAll()
{

}
