// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// 위 Reference의 코드를 타이핑함. Ch 1.

#ifndef _GAME_ERROR_H
#define _GAME_ERROR_H
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <exception>

namespace gameErrorNS
{
	/*
		에러 코드.
		음수는 게임을 강제 종료 시켜야 하는 치명적인 에러를 나타낸다.
		양수는 게임을 강제 종료 시킬 필요가 없는 경고를 나타낸다.
	*/
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

// GameError 클래스. 게임 엔진을 통해 에러가 감지 됐을 때 던져진다.
// std::exception 을 상속 받는다.
class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;

public : 
	GameError() throw()
		: errorCode(gameErrorNS::FATAL_ERROR)
		, 	message("Undefined Error in game.") {}
	GameError(const GameError& e) throw()
		: std::exception(e)
		, errorCode(e.errorCode)
		, message(e.message) {}
	GameError(int code, const std::string& s) throw() 
		: errorCode(code)
		, message(s){}

	GameError& operator=(const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}

	virtual ~GameError() throw() {};

	// Base Class 로부터 재정의 하는 메소드.
	virtual const char* what() const throw() { return this->getMessage(); }
	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }

};

#endif