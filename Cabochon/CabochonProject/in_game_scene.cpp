//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;
using frameworks::TextureList;

InGameScene::InGameScene()
	:Scene()
{

}
InGameScene::~InGameScene()
{
	releaseAll();
}
void InGameScene::start(Graphics* graphics, Input* input, TextureList* textureList)
{
	if (_started)
		return;

	Scene::start(graphics, input, textureList);


	if (!_marble.initialize(_graphics, 0, 0, 0, _textureList->getTexture(TextureList::TextureName::Marble)))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

	float newWidth = 64;
	_marble.setX(100);
	_marble.setY(100);
	_marble.setScale(newWidth / _marble.getWidth());

	_started = true;
}
void InGameScene::update()
{

}
void InGameScene::lateUpdate()
{

}
void InGameScene::render()
{
	_marble.draw();
}

void InGameScene::releaseAll()
{

}

void InGameScene::resetAll()
{

}
