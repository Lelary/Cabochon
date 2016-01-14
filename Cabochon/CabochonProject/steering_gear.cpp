//2016. 1. 15.
#include "steering_gear.h"
using components::SteeringGear;
using mathematics::Angle;

SteeringGear::SteeringGear()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringGear::SteeringGear(const Angle& angle)
	:_angle(angle)
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringGear::SteeringGear(const SteeringGear& rhs)
	: Object(rhs), _angle(rhs._angle)
{
	/*
	2016. 1. 15
	���� �ڱ� ���� ó���� ���� �ʾƵ� ��
	*/
}
SteeringGear::~SteeringGear()
{
	/*
	2016. 1. 15
	nothing to do.
	*/
}
SteeringGear& SteeringGear::operator=(const SteeringGear& rhs)
{
	if (&rhs == this)
		return *this;

	_angle = rhs._angle;
	return *this;
}

Angle SteeringGear::getAngle() const
{
	return _angle;
}
void SteeringGear::setAngle(Angle angle)
{
	/*
	2016. 1. 15
	�߰����� ���� ���� ó��?
	*/
	_angle = angle;
}