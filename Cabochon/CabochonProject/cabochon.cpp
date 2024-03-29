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
	// 콘솔로부터 명령을 얻는다.
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

	// Pre : Game::colsoleCommand()의 복사. ( return 형이 void로 , command를 넘겨주지 않기때문에 복사. (getCommand()는 한번호출될때 내용물을 비워버림.) )
	// Post : Cabochon 게임에서 필요한 치트코드.
	
#if defined(DEBUG) | defined(_DEBUG)
	if (_currentScene == nullptr)	// typeid 를 사용해도 되는지 검사.
		return;
	if (typeid(*_currentScene)!=typeid(scenes::InGameScene))	// static_cast 를 사용해도 되는지 검사.
		return;
	if (static_cast<InGameScene*>(_currentScene)->getBoardState() != controls::BoardState::Play)	// currentMarble을 참조해도 될지 검사.
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
	// resetAll()과 역순.

	if (_currentScene != nullptr)
		_currentScene->releaseAll();

	_text.onLostDevice();
	_textureList.onLostDevice();
	
	Game::releaseAll();
	return;
}
void Cabochon::resetAll()
{
	// releaseAll()과 역순.

	Game::resetAll();
	_textureList.onResetDevice();
	_text.onLostDevice();

	if(_currentScene!=nullptr)
		_currentScene->resetAll();
	return;
}

void Cabochon::changeScene(scenes::SceneName newSceneName)
{
	// 잘못된 SceneName.
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