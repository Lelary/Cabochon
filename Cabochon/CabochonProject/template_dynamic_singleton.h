#ifndef _TEMPLATE_DYNAMIC_SINGLETON_H
#define _TEMPLATE_DYNAMIC_SINGLETON_H

#include "patterns.h"
using patterns::TemplateDynamicSingleton;
template < typename T >
class TemplateDynamicSingleton
{
private:
	TemplateDynamicSingleton(){};
	virtual ~TemplateDynamicSingleton(){};
	static T* _instance;
public:
	static T* getInstance()
	{
		if (_instance == nullptr)
			_instance = new TemplateDynamicSingleton;
		return _instance;
	}

	static void destroyInstance()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}


};
template <typename T>
T* TemplateDynamicSingleton<T> ::_instance = nullptr;

#endif