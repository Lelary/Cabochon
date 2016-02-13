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

	float newWidth = 50;

	for (int i = 0; i < _marbles.size(); i++)
	{
		if (!_marbles[i].initialize(_graphics, 0, 0, 0, _textureList->getTexture(TextureList::TextureName::Marble)))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Image"));

		_marbles[i].setX(i*newWidth);
		_marbles[i].setY(0);
		_marbles[i].setScale(newWidth / _marbles[i].getWidth());
	}
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
	for (int i = 0; i < _marbles.size(); i++)
		_marbles[i].draw();
}

void InGameScene::releaseAll()
{

}

void InGameScene::resetAll()
{

}
