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
	if (y < 0.0f || y> height * maxY)
		return RowType::none;

	if (y / (2 * height) > height)
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
	if (x < 0.0f || x> width * maxX)
		return false;

	//grid �ȿ� ����
	if (y < 0.0f || y> height * maxY)
		return false;
	
	//�߰� üũ
	if (getRowType(y) == RowType::odd)
	{
		if (x < width / 2.0f || x > width * maxX - width / 2.0f)
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
bool Grid::isInGrid(Position position, IntPosition gridPosition)
{
	return isInGrid(position._x, position._y, gridPosition._x, gridPosition._y);
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
bool Grid::isInGridSub(Position position, Quadrant q)
{
	return isInGridSub(position._x, position._y, q);
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
bool Grid::isInGridSub(Position position, IntPosition gridPosition, Quadrant q)
{
	return isInGridSub(position._x, position._y, gridPosition._x, gridPosition._y, q);
}

/*
	2016. 1. 16
	���� ���� �Լ�
*/
Grid::Quadrant Grid::getQuadrant(scalar x, scalar y)
{
	IntPosition gridPosition;
	Position position;

	//grid �ȿ� ����
	if (isInGrid(x, y) == false)
		return Quadrant::none;
	
	//x, y �� ���� ĭ ��ȣ�� ����
	gridPosition = getGridPosition(x, y);
	
	//ĭ��ȣ�� ���� ĭ �������� ����� ��ġ�� ����.
	position._x = x - gridPosition._x * width;
	position._y = y - gridPosition._y * height;

	//����� ��ġ�κ��� �ش�ĭ���� ��� ��и鿡 ���ϴ��� ����
	if (position._x > width / 2.0f)
	{
		if (position._y > height / 2.0f)
			return Quadrant::first;
		else
			return Quadrant::fourth;
	}
	else
	{
		if (position._y > height / 2.0f)
			return Quadrant::second;
		else
			return Quadrant::third;
	}

}
Grid::Quadrant Grid::getQuadrant(Position position)
{
	return getQuadrant(position._x, position._y);
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
		return{ static_cast<int>(x / width), static_cast<int>(y / height) };
	else
		return{ static_cast<int>((x + width / 2) / width), static_cast<int>(y / height) };
}
IntPosition Grid::getGridPosition(Position position)
{
	return getGridPosition(position._x, position._y);
}
