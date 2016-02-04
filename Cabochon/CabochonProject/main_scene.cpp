//2016. 2. 4

#include "main_scene.h"
using frameworks::MainScene;
using frameworks::TextureList;
void MainScene::start(Graphics* graphics, std::vector<TextureManager>* textures)
{
	if (_started)
		return;

	Scene::start(graphics, textures);
	
	if (!startButton.initialize(_graphics, 0, 0, 0, &(*textures)[static_cast<int>(TextureList::BUTTONS)]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	startButton.setX(GAME_WIDTH / 2);
	startButton.setY(GAME_HEIGHT * (3/4));
	startButton.setScale(5);

	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

	_started = true;
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
