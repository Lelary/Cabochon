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

	changeScene(SceneName::MainScene);		

	//if (!shipTexture.initialize(graphics, SHIP_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	//if (!ship.initialize(graphics, 0, 0, 0, &shipTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//planet.setX(GAME_WIDTH * 0.5f - planet.getWidth()*0.5f);
	//planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	//ship.setX(GAME_WIDTH / 4);
	//ship.setY(GAME_HEIGHT / 4);

	//ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	//ship.setCurrentFrame(SHIP_START_FRAME);
	//ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	//ship.setDegrees(45.0f);

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
	if (_currentScene != nullptr)
		_currentScene->releaseAll();

	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	if (_currentScene != nullptr)
		_currentScene->resetAll();

	Game::resetAll();
	return;
}

void Cabochon::changeScene(frameworks::SceneName newSceneName)
{
	// Àß¸øµÈ SceneName.
	if (newSceneName == SceneName::Null || newSceneName == SceneName::Num) {
		return;
	
	if (_currentScene != nullptr)
		delete _currentScene;

	if (newSceneName == SceneName::MainScene)
		_currentScene = new MainScene;
	else if (newSceneName == SceneName::InGameScene)
		_currentScene = new InGameScene;

	_currentScene->start();
}