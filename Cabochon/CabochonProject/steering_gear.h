// 2016. 1. 13.
#ifndef _STEERING_GEAR_H
#define _STEERING_GEAR_H
#include "components.h"
#include "object.h"
#include "angle.h"

/*
	2016. 1. 16
	멤버 함수 작성 1차 완료
*/
namespace components
{
	using components::SteeringGear;
	using mathematics::Angle;

	class SteeringGear
		:public Object
	{
	private:
		Angle _angle;

	public:
		SteeringGear();
		SteeringGear(const Angle& angle);
		SteeringGear(const SteeringGear& rhs);
		virtual ~SteeringGear();
		SteeringGear& operator=(const SteeringGear& rhs);

		Angle getAngle() const;
		void setAngle(Angle angle);

	};
}
#endif //_STEERING_GEAR_H