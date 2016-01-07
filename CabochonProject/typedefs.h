#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include "frameworks.h"
#include "patterns.h"
typedef float scalar;

namespace frameworks
{
	//typedef DirectX9 Graphics;
	//typedef Windows System;
	typedef Console System;
}

namespace patterns
{

	/*
	//typedef 구문으로 Singleton 클래스들중 하나를 선택해서 Singleton 이름을 지정하여 사용할 수 있다.
	typedef DynamicSingleton Singleton;
	*/

	//TemplateDynamicSingleton 클래스를 typedef 할 경우 template 구문 때문에 아래와 같은 우회적인 방법을 사용해야 한다.
	//방법 1
	template <typename T>
	struct Singleton{
	typedef TemplateDynamicSingleton<T> singleton;
	};
	/*
	//방법2 라고 하는데 이걸사용하면 error C2504 발생
	template<class T>
	using Singleton = TemplateDynamicSingleton <T>;
	*/
}
#endif