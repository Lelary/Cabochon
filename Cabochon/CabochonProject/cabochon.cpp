// 2016. 2. 2.

#include "cabochon.h"
using frameworks::SceneName;
using frameworks::Scene;
using frameworks::MainScene;
using frameworks::InGameScene;

Cabochon::Cabochon() 
{
	_currentScene = nullptr;
}

Cabochon::~Cabochon()
{
	if (_currentScene != nullptr)
		delete _currentScene;

	releaseAll();
}

void Cabochon::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	textureList.loadTextures(graphics);

	changeScene(SceneName::MainScene);		
	
	return;
}

void Cabochon::update()
{
	if (_currentScene != nullptr)
		_currentScene->update();
}
void Cabochon::ai(){}
void Cabochon::collisions(){}
void Cabochon::render()
{
	graphics->spriteBegin();

	if (_currentScene != nullptr)
		_currentScene->render();

	graphics->spriteEnd();
}
void Cabochon::releaseAll()
{
	textureList.onLostDevice();
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	textureList.onResetDevice();
	Game::resetAll();
	return;
}

void Cabochon::changeScene(frameworks::SceneName newSceneName)
{
	// Àß¸øµÈ SceneName.
	if (newSceneName == SceneName::Null || newSceneName == SceneName::Num)
		return;

	if (_currentScene != nullptr)
		delete _currentScene;

	if (newSceneName == SceneName::MainScene)
		_currentScene = new MainScene();
	else if (newSceneName == SceneName::InGameScene)
		_currentScene = new InGameScene();

	_currentScene->start(graphics, &textureList);
	
}