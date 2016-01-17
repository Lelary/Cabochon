#ifndef _TEMPORARY_H
#define _TEMPORARY_H
#include <array>
#include "components.h"
/*
	2016. 1. 10
	���� �ʿ��� constant ����, typedef �����ε�
	��� namespace, class�� ��ġ���Ѿ� ���� ���� �ָ��� ��,
	Ȥ�� ������ Ŭ������ ���� �ۼ����� �ʾ��� ��,
	���

	���Ŀ� �˸��� ��ġ�� �������� �ű�� �� ������ ����
*/

namespace temporary
{
	//-> constants ���� ������Ϸ�
	static const unsigned int radius = 3;

	/*
	2016. 1. 16
	���� ���� �ִ� ũ�� = ������ ������ �ִ� �ִ���ġ +1
	�������� ������ ���� dead zone
	maxX�� 8������ �����δ�
	�ش� ���� even�� ��� 8�̸�, odd �� ��� 8-1=7 �̴�.
	maxY�� ���� ���� ����
	*/
	static const unsigned int maxX = 8;
	static const unsigned int maxY = 12;

	//-> ����?
	typedef std::array<std::array<components::marble_ptr, maxX>, maxY> marble_array;

}

#endif _TEMPORARY_H