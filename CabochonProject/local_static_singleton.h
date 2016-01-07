#ifndef _LOCAL_STATIC_SINGLETON_H
#define _LOCAL_STATIC_SINGLETON_H

#include "patterns.h"
using patterns::LocalStaticSingleton;
class LocalStaticSingleton
{
private:
	LocalStaticSingleton(){};
	LocalStaticSingleton(const LocalStaticSingleton& rhs);
	~LocalStaticSingleton(){};
public:
	static LocalStaticSingleton* getInstance()
	{
		static LocalStaticSingleton instance;
		return &instance;
	}
};
#endif