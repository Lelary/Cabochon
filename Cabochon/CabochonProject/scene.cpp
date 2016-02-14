#include "scene.h"
using frameworks::Scene;
using frameworks::SceneName;
using frameworks::TextureList;

Scene::Scene(Graphics& graphics, Input& input, TextureList& textureList)
	:_started(false), _nextScene(SceneName::Null), _graphics(graphics), _input(input), _textureList(textureList){}

Scene::~Scene()
{

}
void Scene::start()
{
	if (_started)
		return;
	_nextScene = SceneName::Null;
}
SceneName Scene::getNextScene()
{
	return _nextScene;
}