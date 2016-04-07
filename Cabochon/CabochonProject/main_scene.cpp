//2016. 2. 4

#include "main_scene.h"
#include "cabochon_constants.h"
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
	
	if (!_title.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::Title)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));
	if (!_mainMessage.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::MainMessage)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	_title.setX(GAME_WIDTH / 2 - (_title.getWidth()/2.0f));
	_title.setY(GAME_HEIGHT*(1.0f / 4.0f));

	_mainMessage.setX(GAME_WIDTH / 2 - (_mainMessage.getWidth() / 2.0f));
	_mainMessage.setY(GAME_HEIGHT*(3.0f / 4.0f));

	_text.initialize(&_graphics, 14, false, false, cabochon_constants::FONT);
	
	_started = true;
}
void MainScene::update(float frameTime)
{
	if (_input.wasKeyPressed(VK_SPACE))
	{
		_nextScene = SceneName::InGameScene;
	}
}
void MainScene::lateUpdate(float frameTime)
{
	
}
void MainScene::render()
{
	_title.draw();
	_mainMessage.draw();
	std::wstring message = std::wstring(TEXT("version: ")) + cabochon_constants::VERSION + std::wstring(TEXT(" ")) + cabochon_constants::MY_PAGE;

	_text.print(message, 10, 10);
}

void MainScene::releaseAll()
{
	_text.onLostDevice();
}

void MainScene::resetAll()
{
	_text.onResetDevice();
}
