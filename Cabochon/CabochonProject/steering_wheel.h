// 2016. 1. 13.
#ifndef _STEERING_WHEEL_H
#define _STEERING_WHEEL_H
#include "components.h"
#include "object.h"
#include "angle.h"

/*
	2016. 1. 16
	��� �Լ� �ۼ� 1�� �Ϸ�
*/
namespace components
{
	using components::SteeringWheel;
	using mathematics::Angle;

	class SteeringWheel
		:public Object
	{
	private:
		Angle _angle;
		void setAngle(Angle angle);

	public:
		SteeringWheel();
		SteeringWheel(const Angle& angle);
		SteeringWheel(const SteeringWheel& rhs);
		virtual ~SteeringWheel();
		SteeringWheel& operator=(const SteeringWheel& rhs);

		Angle getAngle() const;

		void setOrigin();
		void rotateLeft(unsigned int angle);
		void rotateRight(unsigned int angle);
	};
}
#endif //_STEERING_WHEEL_H