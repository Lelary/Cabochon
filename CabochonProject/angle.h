#ifndef _ANGLE_H
#define _ANGLE_H

#include "mathematics.h"
using mathematics::Angle;
using mathematics::scalar;

class Angle
{
private:
	scalar _degree;
	
public:
	Angle();
	Angle(const Angle& rhs);
	virtual ~Angle();
	Angle& operator=(const Angle& rhs);

	scalar getDegree();
	void setDegree(scalar degree);

	/*
		2016. 1. 11
		operator overloading ÇÊ¼ö
		0 <= degree < 360
	*/

};

#endif