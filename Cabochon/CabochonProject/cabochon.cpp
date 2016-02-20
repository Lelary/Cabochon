// 2016. 2. 2.

#include "cabochon.h"
using scenes::SceneName;
using scenes::Scene;
using scenes::MainScene;
using scenes::InGameScene;

Cabochon::Cabochon() 
{
	_currentScene = nullptr;
}

Cabochon::~Cabochon()
{
	if (_currentScene != nullptr)
		delete _currentScene;

	/*
		2016. 2. 13.
		
		이 소멸자는 프로그램 종료시 호출된다
		기존 코드에서는 releaseAll()을 호출하게 되는데,
		프로그램 종료시에 어느 소멸자가 먼저 호출될지는 알수 없어서
		가상함수를 불러서는 안된다. 
		
		example : _currentScene->releaseAll()	->	오류발생

		그런데, releaseAll()을 이 소멸자에서 호출할 필요가 없다고 생각한다. (이 소멸자가 프로그램 종료 시 호출되기 때문)
		releaseAll()함수에서는 자신의 멤버의 releaseAll() 혹은 release()를다시 호출하는데 이것 보다는
		각각의 멤버 오브젝트가 스스로의 소멸자에서 스스로의 release() 함수를 호출하는 것이 옳다고 생각한다.
		오히려, Scene class 에서 releaseAll 을 가지고 있는편이, 한 Scene이 종료된 뒤 다음 Scene으로 넘어가기 전, 메모리 정리를 위해 필요하다.
	*/

}

void Cabochon::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	_textureList.setGraphics(*graphics);
	_textureList.loadTextures();

	changeScene(SceneName::MainScene);		
	
	return;
}

void Cabochon::update()
{
	if (_currentScene != nullptr)
	{
		_currentScene->update(frameTime);
		_currentScene->lateUpdate(frameTime);
	}
	if (_currentScene->getNextScene() != SceneName::Null)
		changeScene(_currentScene->getNextScene());
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
	// resetAll()과 역순.

	if (_currentScene != nullptr)
		_currentScene->releaseAll();

	_textureList.onLostDevice();
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	// releaseAll()과 역순.

	Game::resetAll();
	_textureList.onResetDevice();

	if(_currentScene!=nullptr)
		_currentScene->resetAll();
	return;
}

void Cabochon::changeScene(scenes::SceneName newSceneName)
{
	// 잘못된 SceneName.
	if (newSceneName == SceneName::Null || newSceneName == SceneName::Num)
		return;

	if (_currentScene != nullptr)
		delete _currentScene;

	if (newSceneName == SceneName::MainScene)
		_currentScene = new MainScene(*graphics, *input, _textureList);
	else if (newSceneName == SceneName::InGameScene)
		_currentScene = new InGameScene(*graphics, *input, _textureList);

	_currentScene->start();
	
}