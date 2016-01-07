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
}
#endif