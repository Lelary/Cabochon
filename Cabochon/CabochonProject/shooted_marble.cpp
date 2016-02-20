// 2016. 1. 17
#include "shooted_marble.h"
#include "cabochon_constants.h"
using components::Object;
using components::ShootedMarble;
using controls::Grid;
using controls::MarbleBoard;
using components::marble_ptr;
using mathematics::scalar;
using mathematics::Position;
using mathematics::Velocity;
using mathematics::Angle;
using components::MarbleColor;
using mathematics::IntPosition;
using cabochon_constants::LEFT_WALL;
using cabochon_constants::RIGHT_WALL;

const scalar ShootedMarble::defaultSpeed = 300;

ShootedMarble::ShootedMarble()
	:Marble(), _velocity({0.0f,0.0f})
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}
ShootedMarble::ShootedMarble(MarbleColor color)
	:Marble(color), _velocity({ 0.0f, 0.0f })
{

}
ShootedMarble::~ShootedMarble()
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}	

void ShootedMarble::setPosition(const Position& position)
{
	_prevCentralPosition = Object::convertOrigin(getPosition(), mathematics::Origin::CENTER, getWidth(), getHeight());
	Object::setPosition(position);
}

void ShootedMarble::setPosition(scalar x, scalar y)
{
	_prevCentralPosition = Object::convertOrigin(getPosition(), mathematics::Origin::CENTER, getWidth(), getHeight());
	Object::setPosition(x, y);
}

void ShootedMarble::setCentralPosition(const Position& position)
{
	_prevCentralPosition = Object::convertOrigin(getPosition(), mathematics::Origin::CENTER, getWidth(), getHeight());
	Object::setCentralPosition(position);
}

void ShootedMarble::setCentralPosition(scalar x, scalar y)
{
	_prevCentralPosition = Object::convertOrigin(getPosition(), mathematics::Origin::CENTER, getWidth(), getHeight());
	Object::setCentralPosition(x, y);
}

Position ShootedMarble::getPrevCentralPosition() const
{
	return _prevCentralPosition;
}

void ShootedMarble::move(const MarbleBoard& board, float frameTIme)
{
	setPosition(getPosition()._x + _velocity._x*frameTIme, getPosition()._y + _velocity._y*frameTIme);

	// 좌우벽
	if (getCentralPosition()._x-getWidth()/2.0f <  LEFT_WALL
		||
		getCentralPosition()._x+getWidth()/2.0f > RIGHT_WALL
		)
		_velocity._x *= -1;
		

	if (getCentralPosition()._y-getHeight()/2.0f < board.getCeilingPosition())
		_velocity._y *= -1;

}
scalar ShootedMarble::getDefaultSpeed()
{
	return defaultSpeed;
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
	_velocity = { speed*sinf(angle.getDegree()*PI / 180.0f), -1 * speed*cosf(angle.getDegree()*PI / 180.0f) };
	
}

void ShootedMarble::setCurrentIndex(IntPosition index)
{
	_prevIndex = _currentIndex;
	_currentIndex = index;
}
IntPosition ShootedMarble::getCurrentIndex() const
{
	return _currentIndex;
}
IntPosition ShootedMarble::getPrevIndex() const
{
	return _prevIndex;
}
bool ShootedMarble::updateIndex(const MarbleBoard& board)
{
	if (board.positionToIndex(getPosition()) != _currentIndex)
	{
		setCurrentIndex(board.positionToIndex(getPosition()));

		int maxY = (board.getRowType(_currentIndex._x) == controls::RowType::Even) ? cabochon_constants::MAX_Y : cabochon_constants::MAX_Y - 1;
		if (_currentIndex._x < 0 || _currentIndex._y<0 || _currentIndex._x>getHeight() || _currentIndex._y >= maxY)
			return false;

		return true;
	}
	return false;
}