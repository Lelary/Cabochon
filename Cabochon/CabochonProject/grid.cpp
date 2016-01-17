#include "grid.h"

using components::Grid;
using mathematics::scalar;
using mathematics::Position;
using mathematics::IntPosition;
using temporary::maxX;
using temporary::maxY;

/*
	2016. 1. 16
	실제 구현 함수
*/
Grid::RowType Grid::getRowType(scalar y)
{
	//grid 안에 없음
	if (y < 0.0f || y> height * maxY)
		return RowType::none;

	if (y / (2 * height) > height)
		return RowType::even;
	else
		return RowType::odd;
}

/*
	2016. 1. 16
	실제 구현 함수
*/
bool Grid::isInGrid(scalar x, scalar y)
{
	//grid 안에 없음
	if (x < 0.0f || x> width * maxX)
		return false;

	//grid 안에 없음
	if (y < 0.0f || y> height * maxY)
		return false;
	
	//추가 체크
	if (getRowType(y) == RowType::odd)
	{
		if (x < width / 2.0f || x > width * maxX - width / 2.0f)
			return false;
	}

	return true;
}
bool Grid::isInGrid(scalar x, scalar y, int gx, int gy)
{
	// 실제 계산된 grid 내에서의 position
	IntPosition gridPosition;

	if (isInGrid(x, y) == false)
		return false;

	gridPosition = getGridPosition(x, y);
	
	// 기대한 위치 gx, gy 와 실제 gridPosition이 일치하는지 검사
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

	// 기대한 값과 일치함
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

	// 기대한 값과 일치함
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
	실제 구현 함수
*/
Grid::Quadrant Grid::getQuadrant(scalar x, scalar y)
{
	IntPosition gridPosition;
	Position position;

	//grid 안에 없음
	if (isInGrid(x, y) == false)
		return Quadrant::none;
	
	//x, y 가 속한 칸 번호를 구함
	gridPosition = getGridPosition(x, y);
	
	//칸번호를 통해 칸 내에서의 상대적 위치를 구함.
	position._x = x - gridPosition._x * width;
	position._y = y - gridPosition._y * height;

	//상대적 위치로부터 해당칸에서 어느 사분면에 속하는지 구함
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
	실제 구현 함수
*/
IntPosition Grid::getGridPosition(scalar x, scalar y)
{
	/*
		2016. 1. 16 
		even, odd 체크해야함 그에 따라 결과가 변함.
	*/

	//grid 안에 없음
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
