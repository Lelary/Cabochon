#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl 과 Interface로 분리할지 고민중
*/

namespace controls
{
	using controls::SteeringWheelControl;
	using components::marble_ptr;
	using components::SteeringWheel;

	/*
		2016. 1. 13
		marble 을 그대로 가지고 있지 않고
		marble_ptr = unique_ptr 로 가지고 있을 것
	*/
	class SteeringWheelControl
	{
	private:
		SteeringWheel steeringWheel;
		marble_ptr marbleCurrent;
		marble_ptr marbleNext;

		/*
			2016. 1. 13
			아직 미작성된 클래스
		*/
		//MarbleGenerator marbleGenerator;
		//Timer timer;

	public:
		SteeringWheelControl();
		SteeringWheelControl(const SteeringWheelControl& rhs)=delete;
		virtual ~SteeringWheelControl();
		SteeringWheelControl& operator=(const SteeringWheelControl& rhs)=delete;

		/*
			2016. 1. 13
			미작성
		*/

	};

}

#endif // _STEERING_WHEEL_CONTROL_H