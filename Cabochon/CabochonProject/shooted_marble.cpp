// 2016. 1. 17
#include "shooted_marble.h"
#include "cabochon_constants.h"
using components::ShootedMarble;
using controls::Grid;
using controls::MarbleBoard;
using components::marble_ptr;
using mathematics::scalar;
using mathematics::Velocity;
using mathematics::Angle;

using cabochon_constants::LEFT_WALL;
using cabochon_constants::RIGHT_WALL;

const scalar ShootedMarble::defaultSpeed = 10;

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

void ShootedMarble::move(const MarbleBoard& board, float frameTIme)
{
	_marble->setPosition(_marble->getPosition()._x + _velocity._x*frameTIme, _marble->getPosition()._y + _velocity._y*frameTIme);

	// 좌우벽
	if (_marble->getPosition()._x <  LEFT_WALL
		||
		_marble->getPosition()._x > RIGHT_WALL
		)
		_velocity._x *= -1;
		

	if (_marble->getPosition()._y > board.getCeilingPosition())
		_velocity._y *= -1;

}
scalar ShootedMarble::getDefaultSpeed()
{
	return defaultSpeed;
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
void ShootedMarble::setVelocity(scalar speed, Angle angle)
{
	/*
	2016. 1. 18.
	0도를 어디로?

	Steering Wheel Control 에서 올 정보. 이므로 윗쪽을 향하는 것이 0도
	*/
	_velocity = { speed*cosf(angle.getDegree()), speed*sinf(angle.getDegree()) };
	
}

void ShootedMarble::setMarble(marble_ptr marble)
{
	_marble = std::move(marble);
}