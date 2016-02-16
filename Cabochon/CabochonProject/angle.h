#ifndef _ANGLE_H
#define _ANGLE_H
#include "mathematics.h"
namespace mathematics
{
/*
	2016. 1. 16.
	cpp �ۼ� 1�� �Ϸ�
*/
	class Angle
	{
	private:
		scalar _degree;

	public:
		Angle();
		Angle(scalar degree);
		Angle(const Angle& rhs);
		virtual ~Angle();
		Angle& operator=(const Angle& rhs);
		Angle operator+(const Angle& rhs);
		Angle operator-(const Angle& rhs);

		scalar getDegree() const;
		void setDegree(scalar degree);
	};
}

#endif