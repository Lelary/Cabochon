//2016. 1. 16.

#include "steering_wheel_control.h"

using controls::SteeringWheelControl;
using mathematics::scalar;
using components::marble_ptr;
using components::SteeringWheel;
using frameworks::TextureList;

SteeringWheelControl::SteeringWheelControl()
{
	/*
	2016. 1. 17
	기본값으로 초기화 된다.
	_steeringWheel(0), _marbleCurrent(nullptr), _marbleNext(nullptr)
	*/
	_steeringWheel.setWidth(100);
	_steeringWheel.setHeight(100);
	_steeringWheel.setCentralPosition(GAME_WIDTH/2.0f, 7*GAME_HEIGHT/8);
}
SteeringWheelControl::~SteeringWheelControl()
{
	/*
	2016. 1. 17.
	nothing to do.
	(smart pointer가 알아서 처리함)
	*/
}

void SteeringWheelControl::loadTextures(TextureList& textureList)
{
	_steeringWheel.loadLayers(textureList);
}
scalar SteeringWheelControl::getDegree() const
{
	return _steeringWheel.getAngle().getDegree();
}


marble_ptr& SteeringWheelControl::getMarbleCurrent()
{
	return _marbleCurrent;
}
marble_ptr& SteeringWheelControl::getMarbleNext()
{
	return _marbleNext;
}

void SteeringWheelControl::setMarbleCurrent(marble_ptr& marble)
{

	_marbleCurrent = std::move(marble);
	_marbleCurrent->setCentralPosition(_steeringWheel.getCentralPosition());
}
void SteeringWheelControl::setMarbleNext(marble_ptr& marble)
{
	_marbleNext = std::move(marble);
}

void SteeringWheelControl::setOrigin()
{
	_steeringWheel.setOrigin();
}
void SteeringWheelControl::rotateLeft(float frameTime)
{
	scalar i = _angularVelocity;
	while (i-- > 0 && (getDegree() > -1*_maxDegree))
	{
		_steeringWheel.rotateLeft(_angularVelocity*frameTime);
		if (_marbleCurrent != nullptr)
			_marbleCurrent->rotate(-1*_angularVelocity*frameTime);
	}

}
void SteeringWheelControl::rotateRight(float frameTime)
{
	scalar i = _angularVelocity;
	while (i-- > 0 && getDegree() < _maxDegree)
	{
		_steeringWheel.rotateRight(_angularVelocity*frameTime);
		if (_marbleCurrent != nullptr)
			_marbleCurrent->rotate(+1 * _angularVelocity*frameTime);
	}
}


void SteeringWheelControl::render()
{
	_steeringWheel.draw();
	if (_marbleCurrent != nullptr)
		_marbleCurrent->draw();
	if (_marbleNext != nullptr)
		_marbleNext->draw();

}
void SteeringWheelControl::update(float frameTime)
{
	_steeringWheel.update(frameTime);

	if (_marbleCurrent != nullptr)
		_marbleCurrent->update(frameTime);
	if (_marbleNext != nullptr)
		_marbleNext->update(frameTime);

}