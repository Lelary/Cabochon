//2016. 1. 15.
#include "steering_wheel.h"
using components::SteeringWheel;
using mathematics::Angle;

SteeringWheel::SteeringWheel()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
	
}
SteeringWheel::SteeringWheel(const Angle& angle)
	:_angle(angle)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringWheel::SteeringWheel(const SteeringWheel& rhs)
	: Object(rhs), _angle(rhs._angle)
{
	/*
	2016. 1. 15
	현재 자기 대입 처리를 하지 않아도 됨
	*/
}
SteeringWheel::~SteeringWheel()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}

void SteeringWheel::initialize()
{
}

SteeringWheel& SteeringWheel::operator=(const SteeringWheel& rhs)
{
	if (&rhs == this)
		return *this;

	_angle = rhs._angle;
	return *this;
}

Angle SteeringWheel::getAngle() const
{
	return _angle;
}
void SteeringWheel::setAngle(Angle angle)
{
	/*
	2016. 1. 15
	추가적인 각도 예외 처리?

	2016. 1. 16
	SteeringWheelControl에서 하자
	*/
	_angle = angle;
}

void SteeringWheel::setOrigin()
{
	setAngle(0);
}
void SteeringWheel::rotateLeft(unsigned int angle)
{
	setAngle(_angle - static_cast<scalar>(angle));
}
void SteeringWheel::rotateRight(unsigned int angle)
{
	setAngle(_angle + static_cast<scalar>(angle));
}