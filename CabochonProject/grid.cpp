#include "grid.h"

using components::Grid;
using mathematics::scalar;
using mathematics::Position;
using mathematics::IntPosition;


bool Grid::isInGrid(scalar x, scalar y, int gx, int gy)
{
	/*
	2016. 1. 15
	아직 미작성
	*/
}
bool Grid::isInGrid(Position position, IntPosition gridPosition)
{
	return isInGrid(position._x, position._y, gridPosition._x, gridPosition._y);
}

bool Grid::isInGridSub(scalar x, scalar y, int gx, int gy, Quadrant q)
{
	/*
	2016. 1. 15
	아직 미작성
	*/
}
bool Grid::isInGridSub(Position position, IntPosition gridPosition, Quadrant q)
{
	return isInGridSub(position._x, position._y, gridPosition._x, gridPosition._y, q);
}

Grid::Quadrant Grid::getQuadrant(scalar x, scalar y)
{
	/*
	2016. 1. 15
	아직 미작성
	*/
}
Grid::Quadrant Grid::getQuadrant(Position position)
{
	return getQuadrant(position._x, position._y);
}

IntPosition Grid::getGridPosition(scalar x, scalar y)
{
	/*
	2016. 1. 15
	아직 미작성
	*/
}
IntPosition Grid::getGridPosition(Position position)
{
	getGridPosition(position._x, position._y);
}