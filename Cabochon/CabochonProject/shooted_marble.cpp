// 2016. 1. 17
#include "shooted_marble.h"
#include "cabochon_constants.h"
using mathematics::scalar;
using mathematics::Position;
using mathematics::Velocity;
using mathematics::Angle;
using mathematics::IntPosition;
using components::Object;
using components::ShootedMarble;
using components::marble_ptr;
using components::MarbleColor;
using controls::MarbleBoard;
using cabochon_constants::LEFT_WALL;
using cabochon_constants::RIGHT_WALL;

const scalar ShootedMarble::defaultSpeed = 600;

ShootedMarble::ShootedMarble(const MarbleBoard& marbleBoard)
	:Marble(), _currentIndex(NO_POSITION), _prevIndex(NO_POSITION), _indexChanged(false), _marbleBoard(marbleBoard)
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}
ShootedMarble::ShootedMarble(MarbleColor color, const MarbleBoard& marbleBoard)
	:Marble(color), _currentIndex(NO_POSITION), _prevIndex(NO_POSITION), _indexChanged(false), _marbleBoard(marbleBoard)
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
	_prevPosition = getPosition();
	Object::setPosition(position);

	// Object::setPosition 에서 부가적으로 한 일을 번복. (현재 _position이 private임.)
	for (Layer& layer : _layers)
	{
		layer.adjustPosition(_prevPosition);
	}
}

void ShootedMarble::setPosition(scalar x, scalar y)
{
	setPosition({ x, y });
}

void ShootedMarble::setCentralPosition(const Position& position)
{
	setPosition(Object::convertOrigin(position, mathematics::Origin::LEFT_TOP, getWidth(), getHeight()));
}

void ShootedMarble::setCentralPosition(scalar x, scalar y)
{
	setPosition(Object::convertOrigin({x, y}, mathematics::Origin::LEFT_TOP, getWidth(), getHeight()));
}

Position ShootedMarble::getPrevCentralPosition() const
{
	return Object::convertOrigin(_prevPosition, mathematics::Origin::CENTER, getWidth(), getHeight());
}

void ShootedMarble::move(const MarbleBoard& board, float frameTIme)
{
	setPosition(getPosition().x + getVelocity().x*frameTIme, getPosition().y + getVelocity().y*frameTIme);

	// 좌우벽
	if (getCentralPosition().x - getWidth() / 2.0f < LEFT_WALL
		||
		getCentralPosition().x + getWidth() / 2.0f > RIGHT_WALL
		)
	{
		setVelocity(getVelocity().x * -1, getVelocity().y);
	}
		

	if (getCentralPosition().y - getHeight() / 2.0f < board.getCeilingPosition())
	{
		setVelocity(getVelocity().x, getVelocity().y * -1);
	}

}
scalar ShootedMarble::getDefaultSpeed()
{
	return defaultSpeed;
}

void ShootedMarble::update(float frameTIme)
{
	Marble::update(frameTIme);
	updateIndex();
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
bool ShootedMarble::indexChanged() const
{
	return _indexChanged;
}
bool ShootedMarble::updateIndex()
{
	IntPosition newIndex = _marbleBoard.positionToIndex(getCentralPosition());
	if (newIndex != _currentIndex)
	{
		if (_marbleBoard.isInvalidIndex(newIndex) == false)
		{
			setCurrentIndex(newIndex);
			return _indexChanged = true;
		}
	}
	
	return _indexChanged=false;
}