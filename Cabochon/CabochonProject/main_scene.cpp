//2016. 2. 4

#include "main_scene.h"
using scenes::MainScene;
using scenes::TextureList;

MainScene::MainScene(Graphics& graphics, Input& input, TextureList& textureList)
	:Scene(graphics, input, textureList)
{
	
}
MainScene::~MainScene()
{
	releaseAll();
}
void MainScene::start()
{
	if (_started)
		return;

	Scene::start();
	
	if (!_startButton.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::StartButton)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));
	if (!_exitButton.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::ExitButton)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	_startButton.setX(GAME_WIDTH / 2 - (_startButton.getWidth()/2.0f));
	_startButton.setY(GAME_HEIGHT*(1.0f / 2.0f));

	_exitButton.setX(GAME_WIDTH / 2 - (_exitButton.getWidth() / 2.0f));
	_exitButton.setY(GAME_HEIGHT*(1.0f / 2.0f)+_exitButton.getHeight()*2);

	_text.initialize(&_graphics, 15, false, false, scenes::default_settings::FONT);

	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

	_started = true;
}
void MainScene::update(float frameTime)
{
	if (_input.isKeyDown(ENTER_KEY))
	{
		_nextScene = SceneName::InGameScene;
	}
}
void MainScene::lateUpdate(float frameTime)
{
	
}
void MainScene::render()
{
	_startButton.draw();
	_exitButton.draw();
	_text.print(" Press Enter Key to Start Game. \n \
				The Button Images are Dummy yet. TT. \
				", 10, 10);
}

void MainScene::releaseAll()
{
	_text.onLostDevice();
}

void MainScene::resetAll()
{
	_text.onResetDevice();
}
