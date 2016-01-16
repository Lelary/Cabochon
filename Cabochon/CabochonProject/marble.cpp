#include "marble.h"
#include "temporary.h"
using components::Marble;
using mathematics::IntPosition;
using temporary::maxX;
using temporary::maxY;

Marble::Marble()
	:_gridPosition({ noPosition, noPosition })
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Marble::Marble(const IntPosition& gridPosition)
	: _gridPosition(gridPosition)
{ 
	/*
	2016. 1. 15
	nothing to do.
	*/
}

Marble::Marble(const Marble& rhs)
	:Object(rhs), _gridPosition(rhs._gridPosition)
{
	/*
	2016. 1. 15
	현재 자기 대입 처리 필요 없음
	*/
}

Marble::~Marble()
{
	/*
	2016. 1. 16
	nothing to do.
	*/
}

Marble& Marble::operator=(const Marble& rhs)
{ 
	if (&rhs == this)
		return *this;

	_gridPosition = rhs._gridPosition;
	return *this;
}

IntPosition Marble::getGridPosition() const
{ 
	return _gridPosition;
}
void Marble::setGridPosition(IntPosition gridPosition)
{ 
	// 범위 검사
	if (gridPosition._x < noPosition || gridPosition._x >= maxX)
		return;

	// 범위 검사
	if (gridPosition._y < noPosition || gridPosition._y >= maxY)
		return;

	_gridPosition = gridPosition;
}