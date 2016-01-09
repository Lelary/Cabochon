#ifndef _PATTERNS_H
#define _PATTERNS_H

/*
	2016. 1. 7.
	Singleton Design Pattern ����
*/

namespace patterns
{
//Ŭ���� ����====================================

	//������ Singleton ����.
	class BasicSingleton;

	//lazy initialization �� ����ϴ� dynamic singleton.
	class DynamicSingleton;
	
	//�ٸ� ������ü�� �Ҹ��ڿ��� �� �̱��� ��ü�� ����ؼ� �ȵ�.
	class LocalStaticSingleton;

	//���ø����� �Ǿ��־� ��ӹ޾� ��� �����ϴ�.
	template < typename T > 
	class TemplateDynamicSingleton;

//===============================================
//typedef ����===================================

	/*
	//typedef �������� Singleton Ŭ�������� �ϳ��� �����ؼ� Singleton �̸��� �����Ͽ� ����� �� �ִ�.
	typedef DynamicSingleton Singleton;
	*/

	//TemplateDynamicSingleton Ŭ������ typedef �� ��� template ���� ������ �Ʒ��� ���� ��ȸ���� ����� ����ؾ� �Ѵ�.
	//��� 1
	template <typename T>
	struct Singleton{
		typedef TemplateDynamicSingleton<T> singleton;
	};
	/*
	//���2 ��� �ϴµ� �̰ɻ���ϸ� error C2504 �߻�
	template<class T>
	using Singleton = TemplateDynamicSingleton <T>;
	*/
//===============================================
}

#endif