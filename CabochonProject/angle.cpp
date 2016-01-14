// 2016. 1. 14.
#include "angle.h"
#include <cmath>

using mathematics::Angle;
using mathematics::scalar;

Angle::Angle()
	:_degree(0)
{

}

Angle::Angle(scalar degree)
{
	setDegree(degree);
}

Angle::Angle(const Angle& rhs)
	: _degree(rhs._degree)
{
	/*
		2016. 1. 14.
		self substitution 이 일어나도 이경우는 상관없음
	*/
}

Angle::~Angle()
{

}

Angle& Angle::operator=(const Angle& rhs)
{
	if (this == &rhs)
		return *this;

	_degree = rhs._degree;

	return *this;
}

Angle Angle::operator+(const Angle& rhs)
{
	return Angle(std::fmodf(_degree + rhs._degree, 360.0f));
}

Angle Angle::operator-(const Angle& rhs)
{
	return Angle(std::fmodf(_degree - rhs._degree, 360.0f));
}

scalar Angle::getDegree() const
{
	return _degree;
}

void Angle::setDegree(scalar degree)
{
	_degree = std::fmodf(degree, 360.0f);
}