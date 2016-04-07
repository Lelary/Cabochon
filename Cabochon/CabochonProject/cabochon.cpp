// 2016. 2. 2.

#include <atlbase.h> // 2016. 4. 8
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

	_text.print(std::wstring(CA2CT(_errorMessage.c_str())), 0, 0);
	graphics->spriteEnd();
}
void Cabochon::consoleCommand()
{
	// �ַܼκ��� ����� ��´�.
	command = console->getCommand();

	if (command == TEXT(""))
		return;
	if (command == TEXT("help"))
	{
		console->print(TEXT("Console Commands:"));
		console->print(TEXT("fps - toggle display of frames per second"));
		return;
	}

	if (command == TEXT("fps"))
	{
		fpsOn = !fpsOn;
		if (fpsOn)
			console->print(TEXT("fps On"));
		else
			console->print(TEXT("fps Off"));
	}

	// Pre : Game::colsoleCommand()�� ����. ( return ���� void�� , command�� �Ѱ����� �ʱ⶧���� ����. (getCommand()�� �ѹ�ȣ��ɶ� ���빰�� �������.) )
	// Post : Cabochon ���ӿ��� �ʿ��� ġƮ�ڵ�.
	
#if defined(DEBUG) | defined(_DEBUG)
	if (_currentScene == nullptr)	// typeid �� ����ص� �Ǵ��� �˻�.
		return;
	if (typeid(*_currentScene)!=typeid(scenes::InGameScene))	// static_cast �� ����ص� �Ǵ��� �˻�.
		return;
	if (static_cast<InGameScene*>(_currentScene)->getBoardState() != controls::BoardState::Play)	// currentMarble�� �����ص� ���� �˻�.
		return;

	if (std::wstring(command, 0, 12) == TEXT("cheat color "))
	{
		std::wstring color(command, 12);

		if (color == TEXT("yellow"))	
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Yellow);
		else if (color == TEXT("green"))
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Green);
		else if (color == TEXT("mint"))
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Mint);
		else if (color == TEXT("blue"))
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Blue);
		else if (color == TEXT("violet"))
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Violet);
		else if (color == TEXT("pink"))
			controls::Cheat::cheatColor(static_cast<InGameScene*>(_currentScene)->getSteeringWheelControl(), components::MarbleColor::Pink);			
	}
#endif
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