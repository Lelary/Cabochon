// 2016. 1. 17
#include "shooted_marble.h"
using components::ShootedMarble;
using components::Grid;

ShootedMarble::ShootedMarble()
{

}
ShootedMarble::~ShootedMarble()
{

}

void ShootedMarble::move()
{
	while (true)
	{
		_marble->setPosition(_marble->getPosition()._x + _velocity._x, _marble->getPosition()._y + _velocity._y);

		//if (_marble->getPosition()._x< Grid::left
		Grid::getLeftWall();
	}
}