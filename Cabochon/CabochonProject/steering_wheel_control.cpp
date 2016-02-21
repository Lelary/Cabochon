//2016. 1. 16.

#include "steering_wheel_control.h"
#include "marble_generator.h"

using mathematics::scalar;
using components::marble_ptr;
using components::SteeringWheel;
using components::MarbleColor;
using controls::SteeringWheelControl;
using scenes::TextureList;
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

	_marbleCurrent = MarbleGenerator::makeMarble();	
	_marbleCurrent->setCentralPosition(_steeringWheel.getCentralPosition());
	_marbleNext = MarbleGenerator::makeMarble();
	_marbleNext->setCentralPosition(
		_steeringWheel.getCentralPosition().x - 120,
		_steeringWheel.getCentralPosition().y + 20);
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

void SteeringWheelControl::setMarbleCurrent(MarbleColor color)
{
	if (_marbleCurrent != nullptr)
		_marbleCurrent->setColor(color);
}
void SteeringWheelControl::setMarbleNext(MarbleColor color)
{
	if (_marbleNext != nullptr)
		_marbleNext->setColor(color);
}

void SteeringWheelControl::setOrigin()
{
	_steeringWheel.setOrigin();
}
void SteeringWheelControl::rotateLeft(float frameTime)
{
	scalar i = angularVelocity;
	while (i-- > 0 && (getDegree() > -1*maxDegree))
	{
		_steeringWheel.rotateLeft(angularVelocity*frameTime);
		if (_marbleCurrent != nullptr)
			_marbleCurrent->rotate(-1*angularVelocity*frameTime);
	}

}
void SteeringWheelControl::rotateRight(float frameTime)
{
	scalar i = angularVelocity;
	while (i-- > 0 && getDegree() < maxDegree)
	{
		_steeringWheel.rotateRight(angularVelocity*frameTime);
		if (_marbleCurrent != nullptr)
			_marbleCurrent->rotate(+1 * angularVelocity*frameTime);
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