//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;
using frameworks::TextureList;

void InGameScene::start(Graphics* graphics, Input* input, TextureList* textureList)
{
	if (_started)
		return;

	Scene::start(graphics, input, textureList);



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

}
