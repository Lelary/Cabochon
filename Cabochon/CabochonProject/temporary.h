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
	// ���� ���� �ִ� ũ�� = ������ ������ �ִ� �ִ���ġ +1
	// �������� ������ ���� dead zone
	static const unsigned int maxX = 6;
	static const unsigned int maxY = 10;
	typedef std::array<std::array<components::marble_ptr, maxX>, maxY> marble_array;

}

#endif _TEMPORARY_H