//2016. 2. 4

#include "in_game_scene.h"
using frameworks::InGameScene;
using frameworks::TextureList;

InGameScene::InGameScene(Graphics& graphics, Input& input, TextureList& textureList)
	:Scene(graphics, input, textureList)
{
	
}
InGameScene::~InGameScene()
{
	releaseAll();
}
void InGameScene::start()
{
	if (_started)
		return;

	Scene::start();

	_backGround.initialize(&_graphics, 0, 0, 0, _textureList.getTexture(TextureList::TextureName::BackGroundMountain));

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
	_backGround.draw();
	_wheelControl.render();
}

void InGameScene::releaseAll()
{

}

void InGameScene::resetAll()
{

}
