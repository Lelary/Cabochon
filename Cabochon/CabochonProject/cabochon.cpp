// 2016. 2. 2.

#include "cabochon.h"
#include "cheat.h"
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

	_text.initialize(graphics, 15, false, false, cabochon_constants::FONT);

	changeScene(SceneName::MainScene);		
	
	return;
}

void Cabochon::update()
{
	if (_currentScene != nullptr)
	{
		try {
			_currentScene->update(frameTime);
		}
		catch (const GameError& e)
		{
			_errorMessage=e.getMessage()+std::string("\n was occured in update()");
		}
		catch (const std::exception& e)
		{
			_errorMessage = e.what();
		}
		try{
			_currentScene->lateUpdate(frameTime);
		}
		catch (const GameError& e)
		{
			_errorMessage=e.getMessage() + std::string("\n was occured in late update()");
		}
		catch (const std::exception& e)
		{
			_errorMessage = e.what();
		}
	}
	if (_currentScene->getNextScene() != SceneName::None)
		changeScene(_currentScene->getNextScene());
}
void Cabochon::ai(){}
void Cabochon::collisions(){}
void Cabochon::render()
{
	graphics->spriteBegin();
	if (_currentScene != nullptr)
		_currentScene->render();

	_text.print(_errorMessage, 0, 0);
	graphics->spriteEnd();
}
void Cabochon::consoleCommand()
{
	// �ַܼκ��� ����� ��´�.
	command = console->getCommand();
	if (command == "")
		return;
	if (command == "help")
	{
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		return;
	}

	if (command == "fps")
	{
		fpsOn = !fpsOn;
		if (fpsOn)
			console->print("fps On");
		else
			console->print("fps Off");
	}
	//=======================================================

	if (typeid(*_currentScene)!=typeid(scenes::InGameScene))
		return;
	if (static_cast<InGameScene*>(_currentScene)->getBoardState() != controls::BoardState::Play)
		return;

	if (std::string(command, 0, 12) == "cheat color ")
	{
		std::string color(command, 12);

		if (color == "red")	
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Red);
		else if (color == "orange")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Orange);
		else if (color == "yellow")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Yellow);
		else if (color == "green")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Green);
		else if (color == "blue")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Blue);
		else if (color == "purple")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Purple);
		else if (color == "gray")
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Gray);
	}

}
void Cabochon::releaseAll()
{
	// resetAll()�� ����.

	if (_currentScene != nullptr)
		_currentScene->releaseAll();

	_text.onLostDevice();
	_textureList.onLostDevice();
	
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	// releaseAll()�� ����.

	Game::resetAll();
	_textureList.onResetDevice();
	_text.onLostDevice();

	if(_currentScene!=nullptr)
		_currentScene->resetAll();
	return;
}

void Cabochon::changeScene(scenes::SceneName newSceneName)
{
	// �߸��� SceneName.
	if (newSceneName == SceneName::None || newSceneName == SceneName::Num)
		return;

	if (_currentScene != nullptr)
		delete _currentScene;

	if (newSceneName == SceneName::MainScene)
		_currentScene = new MainScene(*graphics, *input, _textureList);
	else if (newSceneName == SceneName::InGameScene)
		_currentScene = new InGameScene(*graphics, *input, _textureList);

	_currentScene->start();
	
}