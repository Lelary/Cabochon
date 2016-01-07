#ifndef _PATTERNS_H
#define _PATTERNS_H

/*
	2016. 1. 7.
	Singleton Design Pattern 모음
*/

namespace patterns
{
	//정적인 Singleton 제공.
	class BasicSingleton;

	//lazy initialization 을 사용하는 dynamic singleton.
	class DynamicSingleton;
	
	//다른 전역객체의 소멸자에서 이 싱글톤 객체를 사용해선 안됨.
	class LocalStaticSingleton;

	//템플릿으로 되어있어 상속받아 사용 가능하다.
	template < typename T > 
	class TemplateDynamicSingleton;
}

#endif