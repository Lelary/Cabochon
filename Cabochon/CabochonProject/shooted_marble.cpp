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
	:Marble(), _velocity({ 0.0f, 0.0f }), _currentIndex(NO_POSITION), _prevIndex(NO_POSITION), _indexChanged(false), _marbleBoard(marbleBoard)
{
	/*
	2016. 1. 18.
	nothing to do.
	*/
}
ShootedMarble::ShootedMarble(MarbleColor color, const MarbleBoard& marbleBoard)
	:Marble(color), _velocity({ 0.0f, 0.0f }), _currentIndex(NO_POSITION), _prevIndex(NO_POSITION), _indexChanged(false), _marbleBoard(marbleBoard)
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

	// Object::setPosition ���� �ΰ������� �� ���� ����. (���� _position�� private��.)
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
	setPosition(getPosition().x + _velocity.x*frameTIme, getPosition().y + _velocity.y*frameTIme);

	// �¿캮
	if (getCentralPosition().x-getWidth()/2.0f <  LEFT_WALL
		||
		getCentralPosition().x+getWidth()/2.0f > RIGHT_WALL
		)
		_velocity.x *= -1;
		

	if (getCentralPosition().y-getHeight()/2.0f < board.getCeilingPosition())
		_velocity.y *= -1;

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
	0���� ����?

	Steering Wheel Control ���� �� ����. �̹Ƿ� ������ ���ϴ� ���� 0��
	*/
	_velocity = { speed*sinf(angle.getDegree()*PI / 180.0f), -1 * speed*cosf(angle.getDegree()*PI / 180.0f) };
	
}
void ShootedMarble::update(float frameTIme)
{
	Marble::update(frameTIme);
	updateIndex(_marbleBoard);
}

void ShootedMarble::setCurrentIndex(IntPosition index)
{
	//prevIndex�� ������ ������Ʈ������ ����. (���� ��ġ�� ������ ���� �ִ�.)
	if(isInInvalidIndex()==false)
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
bool ShootedMarble::updateIndex(const MarbleBoard& board)
{
	if (board.positionToIndex(getCentralPosition()) != _currentIndex)
	{
		setCurrentIndex(board.positionToIndex(getCentralPosition()));

		return _indexChanged = true;
	}
	return _indexChanged = false;
}
bool ShootedMarble::isInInvalidIndex() const
{
	return _marbleBoard.isInvalidIndex(_currentIndex);
}

bool ShootedMarble:: wasInInvalidIndex() const
{
	return _marbleBoard.isInvalidIndex(_prevIndex);
}