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
	���� �ڱ� ���� ó�� �ʿ� ����
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

bool Marble::circularHitTest(const Marble& anotherMarble) const
{
	return circularHitTest(*this, anotherMarble);
}
bool Marble::circularHitTest(const Marble& marble1, const Marble& marble2)
{
	/* 
		2016. 1. 22.
		Marble ��ü�� Width = Height = 2*radius
		����� radius ��������� �����Ƿ� �̸� �̿��Ѵ�.
	*/
	scalar radius1 = marble1.getWidth() / 2.0f;
	scalar radius2 = marble2.getWidth() / 2.0f;

	scalar distanceSquare =
		powf((marble2.getCentralPosition()._x - marble1.getCentralPosition()._x), 2.0f)
		-
		powf((marble2.getCentralPosition()._y - marble1.getCentralPosition()._y), 2.0f);
	
	//���������� �� ������.
	if (powf(radius1 + radius2, 2.0f) < distanceSquare)
		return false;
	else
		return true;
}
