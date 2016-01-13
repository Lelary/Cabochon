#ifndef _GRID_H
#define _GRID_H

#include "mathematics.h"
#include "temporary.h"
#include "components.h"
using mathematics::scalar;
using components::Grid;
using namespace temporary;
using temporary::maxX;
using temporary::maxY;
using mathematics::Vector2;
using temporary::radius;

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
	static const int width;
	static const int height;
	//��и�
	enum class Quadrant{ none, first = 1, second, third, fourth, num };
public:
/*
	2016. 1. 10
	�Լ������ �ٽ� �����غ�����

	2016. 1. 13
	���� �Լ����� ������ �� ����
*/
	Grid() = delete;
	Grid(const Grid& rhs) = delete;
	~Grid() = delete;

	static bool isInGrid(scalar x, scalar y, int gx, int gy);
	static bool isInGridSub(scalar x, scalar y, int gx, int gy, Quadrant q);

	static Quadrant getQuadrant(scalar x, scalar y);
	static Vector2<int> getGridPosition(scalar x, scalar y);

};
// radius of marble.. 
const int Grid::width = radius;
const int Grid::height = radius;

#endif