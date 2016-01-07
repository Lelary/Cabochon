#ifndef _DYNAMIC_SINGLETON_H
#define _DYNAMIC_SINGLETON_H

#include "patterns.h"
using patterns::DynamicSingleton;
class DynamicSingleton
{
private:
	DynamicSingleton(){};
	DynamicSingleton(const DynamicSingleton& rhs);
	~DynamicSingleton(){};

	static DynamicSingleton* _instance;
public:
	static DynamicSingleton* getInstance()
	{
		if (_instance == nullptr)
			_instance = new DynamicSingleton;
		return _instance;
	}
};
DynamicSingleton* DynamicSingleton::_instance = nullptr;

#endif