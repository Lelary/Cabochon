#include "scene.h"
using frameworks::Scene;
using frameworks::SceneName;
using frameworks::TextureList;

Scene::Scene()
	:_started(false), _nextScene(SceneName::Null), _graphics(nullptr), _input(nullptr), _textureList(nullptr){}

Scene::~Scene()
{

}
void Scene::start(Graphics* graphics, Input* input, TextureList* textureList)
{
	if (_started)
		return;
	_nextScene = SceneName::Null;
	_graphics = graphics;
	_input = input;
	_textureList = textureList;
}
SceneName Scene::getNextScene()
{
	return _nextScene;
}