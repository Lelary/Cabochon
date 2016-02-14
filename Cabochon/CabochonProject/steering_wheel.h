// 2016. 1. 13.
#ifndef _STEERING_WHEEL_H
#define _STEERING_WHEEL_H
#include "components.h"
#include "object.h"
#include "angle.h"
#include <array>

/*
	2016. 1. 16
	멤버 함수 작성 1차 완료
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

		static const int numImages = 3;
		std::array<Image, numImages> _images;

		void setAngle(Angle angle);

	public:
		SteeringWheel();
		SteeringWheel(const Angle& angle);
		SteeringWheel(const SteeringWheel& rhs);
		virtual ~SteeringWheel();
		SteeringWheel& operator=(const SteeringWheel& rhs);

		void initialize();

		Angle getAngle() const;

		void setOrigin();
		void rotateLeft(unsigned int angle);
		void rotateRight(unsigned int angle);

		void draw();
	};
}
#endif //_STEERING_WHEEL_H
