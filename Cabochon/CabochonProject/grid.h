#ifndef _GRID_H
#define _GRID_H

#include "typedefs.h"
#include "temporary.h"
#include "components.h"
#include <tuple>
using components::Grid;
using namespace temporary;
using temporary::maxX;
using temporary::maxY;

/*
	2016. 1. 10
	Block -> Quadrant -> Grid

	odd - even �� �ݺ��Ǵ� 
	����� ������ �����ؾ��Ѵ�.
	�������� ������ ������ �� �� �� �ִ�.

	��ĭ�� �ʺ�� ���̸� �˾ƾ��Ѵ�. -> Marble�� ����
	�̷κ��� �־��� Marble�� ��ġ�� ��� ĭ�� �ش��ϴ��� ������� �� �� �ִ�.

	�Ķ���ͷ� Marble�� �޴� ���� ��ǥ�� �޴°�츦 �����ε� �� �� �ִ�.
*/

/*
	2016. 1. 10
	������ ��ǥ�� ���� ��ġ�� ������ش�.
*/
class Grid
{
private:
	int width;
	int height;
	//��и�
	enum Quadrant{ none, one = 0, two, three, four, num };
public:
/*
	2016. 1. 10
	�Լ������ �ٽ� �����غ�����
*/

	static bool isIn(scalar x, scalar y);
	static bool isInSub(scalar x, scalar y);

	static Quadrant getQuadrant(scalar x, scalar y);

	//typedef�ʿ�
	std::tuple<int, int> isWhere(scalar x, scalar y);

	
};

#endif