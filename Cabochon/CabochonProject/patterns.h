#ifndef _PATTERNS_H
#define _PATTERNS_H

/*
	2016. 1. 7.
	Singleton Design Pattern 모음
*/

namespace patterns
{
//클래스 선언====================================

	//정적인 Singleton 제공.
	class BasicSingleton;

	//lazy initialization 을 사용하는 dynamic singleton.
	class DynamicSingleton;
	
	//다른 전역객체의 소멸자에서 이 싱글톤 객체를 사용해선 안됨.
	class LocalStaticSingleton;

	//템플릿으로 되어있어 상속받아 사용 가능하다.
	template < typename T > 
	class TemplateDynamicSingleton;

//===============================================
//typedef 구문===================================

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
//===============================================
}

#endif