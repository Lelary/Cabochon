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
	_wheelControl.loadTextures(_textureList);


	_wheelControl.setMarbleCurrent(MarbleGenerator::loadTexture(MarbleGenerator::makeMarble(), _textureList));


	_started = true;
}
void InGameScene::update()
{
	_wheelControl.update();
}
void InGameScene::lateUpdate()
{

}
void InGameScene::render()
{
	_backGround.draw();
	_wheelControl.render();
	_marbleControl.render();
}

void InGameScene::releaseAll()
{

}

void InGameScene::resetAll()
{

}
