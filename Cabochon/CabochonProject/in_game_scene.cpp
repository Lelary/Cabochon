//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;

void InGameScene::start(Graphics* graphics, std::vector<TextureManager>* textures)
{
	if (_started)
		return;

	Scene::start(graphics, textures);



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
