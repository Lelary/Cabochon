#ifndef _TEMPORARY_H
#define _TEMPORARY_H
#include <array>
#include "components.h"
#include "mathematics.h"
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
	using mathematics::scalar;
	//-> constants ���� ������Ϸ�
	//static const unsigned int radius = 3;

	/*
	2016. 1. 16
	���� ���� �ִ� ũ�� = ������ ������ �ִ� �ִ���ġ +1
	�������� ������ ���� dead zone
	maxX�� 8������ �����δ�
	�ش� ���� even�� ��� 8�̸�, odd �� ��� 8-1=7 �̴�.
	maxY�� ���� ���� ����
	*/
	static const unsigned int maxX = 8;
	static const unsigned int maxY = 10;

	/*
	2016. 1. 21.
	constants
	*/
	static const unsigned int boardWidth = 100;
	static const unsigned int boardHeight = 120;
	static const unsigned int deckHeight = 30;
	static const scalar blockWidth = static_cast<scalar>(boardWidth) / static_cast<scalar>(maxX);
	static const scalar blockHeight = blockWidth;
	static const scalar marbleRadius = blockWidth * 0.9f / 2.0f;
	static const unsigned int boardMargin = 10;

	//static const unsigned int ceiling = 10;
	//static const unsigned int floor = ceiling + boardHeight;


	//-> ����?
	typedef std::array<std::array<components::marble_ptr, maxX>, maxY> marble_array;

}

#endif _TEMPORARY_H