#ifndef _PATTERNS_H
#define _PATTERNS_H

/*
	2016. 1. 7.
	Singleton Design Pattern ����
*/

namespace patterns
{
	//������ Singleton ����.
	class BasicSingleton;

	//lazy initialization �� ����ϴ� dynamic singleton.
	class DynamicSingleton;
	
	//�ٸ� ������ü�� �Ҹ��ڿ��� �� �̱��� ��ü�� ����ؼ� �ȵ�.
	class LocalStaticSingleton;

	//���ø����� �Ǿ��־� ��ӹ޾� ��� �����ϴ�.
	template < typename T > 
	class TemplateDynamicSingleton;
}

#endif