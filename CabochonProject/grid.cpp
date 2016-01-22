#include "grid.h"

using components::Grid;
using mathematics::scalar;
using mathematics::Position;
using mathematics::IntPosition;
using temporary::maxX;
using temporary::maxY;

/*
	2016. 1. 16
	���� ���� �Լ�
*/
Grid::RowType Grid::getRowType(scalar y)
{
	//grid �ȿ� ����
	if (y < 0.0f || y> blockHeight * maxY)
		return RowType::none;

	if (y / (2 * blockHeight) > blockHeight)
		return RowType::even;
	else
		return RowType::odd;
}
Grid::RowType Grid::getRowType(int y)
{
	//grid �ȿ� ����
	if (y < 0 || y >= maxY)
		return RowType::none;

	if (y%2 == 0)
		return RowType::even;
	else
		return RowType::odd;
}

/*
	2016. 1. 16
	���� ���� �Լ�
*/
bool Grid::isInGrid(scalar x, scalar y)
{
	//grid �ȿ� ����
	if (x < 0.0f || x> blockWidth * maxX)
		return false;

	//grid �ȿ� ����
	if (y < 0.0f || y> blockHeight * maxY)
		return false;
	
	//�߰� üũ
	if (getRowType(y) == RowType::odd)
	{
		if (x < blockWidth / 2.0f || x > blockWidth * maxX - blockWidth / 2.0f)
			return false;
	}

	return true;
}
bool Grid::isInGrid(scalar x, scalar y, int gx, int gy)
{
	// ���� ���� grid �������� position
	IntPosition gridPosition;

	if (isInGrid(x, y) == false)
		return false;

	gridPosition = getGridPosition(x, y);
	
	// ����� ��ġ gx, gy �� ���� gridPosition�� ��ġ�ϴ��� �˻�
	if (gridPosition._x == gx
		&&
		gridPosition._y == gy)
		return true;
	else
		return false;
}
bool Grid::isInGrid(Position centralPosition, IntPosition gridPosition)
{
	return isInGrid(centralPosition._x, centralPosition._y, gridPosition._x, gridPosition._y);
}

bool Grid::isInGridSub(scalar x, scalar y, Quadrant q)
{
	if (isInGrid(x, y) == false)
		return false;

	// ����� ���� ��ġ��
	if (q == getQuadrant(x, y))
		return true;
	else
		return false;
}
bool Grid::isInGridSub(Position centralPosition, Quadrant q)
{
	return isInGridSub(centralPosition._x, centralPosition._y, q);
}
bool Grid::isInGridSub(scalar x, scalar y, int gx, int gy, Quadrant q)
{
	if (isInGrid(x, y, gx, gy) == false)
		return false;

	// ����� ���� ��ġ��
	if (q == getQuadrant(x, y))
		return true;
	else
		return false;

}
bool Grid::isInGridSub(Position centralPosition, IntPosition gridPosition, Quadrant q)
{
	return isInGridSub(centralPosition._x, centralPosition._y, gridPosition._x, gridPosition._y, q);
}

/*
	2016. 1. 16
	���� ���� �Լ�
*/
Grid::Quadrant Grid::getQuadrant(scalar x, scalar y)
{
	IntPosition gridPosition;
	Position centralPosition;

	//grid �ȿ� ����
	if (isInGrid(x, y) == false)
		return Quadrant::none;
	
	//x, y �� ���� ĭ ��ȣ�� ����
	gridPosition = getGridPosition(x, y);
	
	//ĭ��ȣ�� ���� ĭ �������� ����� ��ġ�� ����.
	centralPosition._x = x - gridPosition._x * blockWidth;
	centralPosition._y = y - gridPosition._y * blockHeight;

	//����� ��ġ�κ��� �ش�ĭ���� ��� ��и鿡 ���ϴ��� ����
	if (centralPosition._x > blockWidth / 2.0f)
	{
		if (centralPosition._y > blockHeight / 2.0f)
			return Quadrant::first;
		else
			return Quadrant::fourth;
	}
	else
	{
		if (centralPosition._y > blockHeight / 2.0f)
			return Quadrant::second;
		else
			return Quadrant::third;
	}

}
Grid::Quadrant Grid::getQuadrant(Position centralPosition)
{
	return getQuadrant(centralPosition._x, centralPosition._y);
}

/*
	2016. 1. 16
	���� ���� �Լ�
*/
IntPosition Grid::getGridPosition(scalar x, scalar y)
{
	/*
		2016. 1. 16 
		even, odd üũ�ؾ��� �׿� ���� ����� ����.
	*/

	//grid �ȿ� ����
	if (isInGrid(x, y) == false)
		return{ -1, -1 };

	if (getRowType(y) == RowType::even)
		return{ static_cast<int>(x / blockWidth), static_cast<int>(y / blockHeight) };
	else
		return{ static_cast<int>((x + blockWidth / 2) / blockWidth), static_cast<int>(y / blockHeight) };
}
IntPosition Grid::getGridPosition(Position centralPosition)
{
	return getGridPosition(centralPosition._x, centralPosition._y);
}

int Grid::getLeftWall()
{
	return leftWall;
}
int Grid::getRightWall()
{
	return rightWall;
}
int Grid::getCeiling()
{
	return ceiling;
}
int Grid::getFloor()
{
	return floor;
}