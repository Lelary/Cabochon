// 2016. 1. 30.
// Reference : "2D Game Programming" , Charles Kelly, 2011
// �� Reference�� �ڵ带 Ÿ������. Ch 1.

#ifndef _GAME_ERROR_H
#define _GAME_ERROR_H
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <exception>

namespace gameErrorNS
{
	/*
		���� �ڵ�.
		������ ������ ���� ���� ���Ѿ� �ϴ� ġ������ ������ ��Ÿ����.
		����� ������ ���� ���� ��ų �ʿ䰡 ���� ��� ��Ÿ����.
	*/
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}

// GameError Ŭ����. ���� ������ ���� ������ ���� ���� �� ��������.
// std::exception �� ��� �޴´�.
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

	// Base Class �κ��� ������ �ϴ� �޼ҵ�.
	virtual const char* what() const throw() { return this->getMessage(); }
	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }

};

#endif