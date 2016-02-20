// 2016. 1. 13.
#ifndef _STEERING_WHEEL_H
#define _STEERING_WHEEL_H
#include "components.h"
#include "object.h"
#include "angle.h"
#include "texture_list.h"
#include <array>

/*
	2016. 1. 16
	멤버 함수 작성 1차 완료
*/
namespace components
{
	using mathematics::Angle;
	using components::SteeringWheel;
	using scenes::TextureList;

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
		void rotateLeft(scalar degree);
		void rotateRight(scalar degree);

		void loadLayers(TextureList& textureList);
		void draw();
		void update(float frameTime);
	};
}
#endif //_STEERING_WHEEL_H
