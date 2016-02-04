#include "scene.h"
using frameworks::Scene;
using frameworks::TextureList;

Scene::Scene()
	:_started(false), _graphics(nullptr), _textureList(nullptr){}

Scene::~Scene()
{

}
void Scene::start(Graphics* graphics, TextureList* textureList)
{
	if (_started)
		return;
	_graphics = graphics;
	_textureList = textureList;
}