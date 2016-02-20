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
		
		�� �Ҹ��ڴ� ���α׷� ����� ȣ��ȴ�
		���� �ڵ忡���� releaseAll()�� ȣ���ϰ� �Ǵµ�,
		���α׷� ����ÿ� ��� �Ҹ��ڰ� ���� ȣ������� �˼� ���
		�����Լ��� �ҷ����� �ȵȴ�. 
		
		example : _currentScene->releaseAll()	->	�����߻�

		�׷���, releaseAll()�� �� �Ҹ��ڿ��� ȣ���� �ʿ䰡 ���ٰ� �����Ѵ�. (�� �Ҹ��ڰ� ���α׷� ���� �� ȣ��Ǳ� ����)
		releaseAll()�Լ������� �ڽ��� ����� releaseAll() Ȥ�� release()���ٽ� ȣ���ϴµ� �̰� ���ٴ�
		������ ��� ������Ʈ�� �������� �Ҹ��ڿ��� �������� release() �Լ��� ȣ���ϴ� ���� �Ǵٰ� �����Ѵ�.
		������, Scene class ���� releaseAll �� ������ �ִ�����, �� Scene�� ����� �� ���� Scene���� �Ѿ�� ��, �޸� ������ ���� �ʿ��ϴ�.
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
	// resetAll()�� ����.

	if (_currentScene != nullptr)
		_currentScene->releaseAll();

	_textureList.onLostDevice();
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	// releaseAll()�� ����.

	Game::resetAll();
	_textureList.onResetDevice();

	if(_currentScene!=nullptr)
		_currentScene->resetAll();
	return;
}

void Cabochon::changeScene(scenes::SceneName newSceneName)
{
	// �߸��� SceneName.
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