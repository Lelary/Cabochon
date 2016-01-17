// 2016. 1. 17
#include "shooted_marble.h"
using components::ShootedMarble;
using components::Grid;
using components::marble_ptr;
using mathematics::Velocity;
using mathematics::Angle;

ShootedMarble::ShootedMarble()
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}
ShootedMarble::ShootedMarble(marble_ptr& marble)
	:_marble(std::move(marble))
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}
ShootedMarble::~ShootedMarble()
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}

void ShootedMarble::move()
{
	while (true)
	{
		_marble->setPosition(_marble->getPosition()._x + _velocity._x, _marble->getPosition()._y + _velocity._y);

		// 좌우벽
		if (_marble->getPosition()._x <  Grid::getLeftWall()
			||
			_marble->getPosition()._x > Grid::getRightWall()
			)
			_velocity._x *= -1;
		

		if (_marble->getPosition()._y > Grid::getCeiling())
			return;		
	}
}

marble_ptr& ShootedMarble::getMarble()
{
	return _marble;
}
Velocity ShootedMarble::getVelocity() const
{
	return _velocity;
}

void ShootedMarble::setVelocity(Velocity velocity)
{
	_velocity = velocity;
}
void ShootedMarble::setVelocity(scalar vx, scalar vy)
{
	_velocity = { vx, vy };
}
void ShootedMarble::setVelocity(scalar speed, scalar angle)
{
	/*
	2016. 1. 18.
	0도를 어디로?

	Steering Wheel Control 에서 올 정보. 이므로 윗쪽을 향하는 것이 0도
	*/
	_velocity = { speed*cosf(angle), speed*sinf(angle) };
	
}

void ShootedMarble::setMarble(marble_ptr& marble)
{
	_marble = std::move(marble);
}