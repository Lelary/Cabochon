#ifndef _BASIC_SINGLETON_H
#define _BASIC_SINGLETON_H

#include "patterns.h"
using patterns::BasicSingleton;
class BasicSingleton
{
private:
	BasicSingleton(){};
	BasicSingleton(const BasicSingleton& rhs);

	static BasicSingleton* _instance;
public:
	static BasicSingleton* getInstance()
	{
		return _instance;
	}
};
BasicSingleton* BasicSingleton::_instance = new BasicSingleton;

#endif