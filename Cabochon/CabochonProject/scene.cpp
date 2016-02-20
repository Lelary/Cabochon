#include "scene.h"
using scenes::Scene;
using scenes::SceneName;
using scenes::TextureList;

Scene::Scene(Graphics& graphics, Input& input, TextureList& textureList)
	:_started(false), _nextScene(SceneName::None), _graphics(graphics), _input(input), _textureList(textureList)
{
}

Scene::~Scene()
{

}
void Scene::start()
{
	if (_started)
		return;
	_nextScene = SceneName::None;
}
SceneName Scene::getNextScene()
{
	return _nextScene;
}