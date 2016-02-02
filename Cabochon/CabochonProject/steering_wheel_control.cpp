//2016. 1. 16.

#include "steering_wheel_control.h"

using controls::SteeringWheelControl;
using mathematics::scalar;
using components::marble_ptr;
using components::SteeringWheel;

SteeringWheelControl::SteeringWheelControl()
{
	/*
	2016. 1. 17
	기본값으로 초기화 된다.
	_steeringWheel(0), _marbleCurrent(nullptr), _marbleNext(nullptr)
	*/
}
SteeringWheelControl::~SteeringWheelControl()
{
	/*
	2016. 1. 17.
	nothing to do.
	(smart pointer가 알아서 처리함)
	*/
}

scalar SteeringWheelControl::getDegree() const
{
	return _steeringWheel.getAngle().getDegree() - 90;
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
}
void SteeringWheelControl::setMarbleNext(marble_ptr& marble)
{
	_marbleNext = std::move(marble);
}

void SteeringWheelControl::setOrigin()
{
	_steeringWheel.setOrigin();
}
void SteeringWheelControl::rotateLeft()
{
	/*
	2017. 1. 17
	키입력 추가 후 수정
	*/
	int i = angularVelocity;
	while (i-- > 0 && getDegree() > -1*absMaxDegree)
		_steeringWheel.rotateLeft(angularVelocity);

}
void SteeringWheelControl::rotateRight()
{

	/*
	2017. 1. 17
	키입력 추가 후 수정
	*/
	int i = angularVelocity;
	while (i-- > 0 && getDegree() < absMaxDegree)
		_steeringWheel.rotateRight(angularVelocity);
}


void SteeringWheelControl::render()
{

}
void SteeringWheelControl::update()
{

}