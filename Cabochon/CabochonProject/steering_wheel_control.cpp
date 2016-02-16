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
	_steeringWheel.setPosition(100, 100);
	_steeringWheel.setWidth(100);
	_steeringWheel.setHeight(100);
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
	scalar i = angularVelocity;
	while (i-- > 0 && (getDegree() > -1*maxDegree))
		_steeringWheel.rotateLeft(angularVelocity*frameTime);

}
void SteeringWheelControl::rotateRight(float frameTime)
{
	scalar i = angularVelocity;
	while (i-- > 0 && getDegree() < maxDegree)
		_steeringWheel.rotateRight(angularVelocity*frameTime);
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


	//장난.
	//_marbleCurrent->setPosition(_marbleCurrent->getPosition()._x + 1.0f,
	//	_marbleCurrent->getPosition()._y);
}