#ifndef _STEERING_GEAR_CONTROL_H
#define _STEERING_GEAR_CONTROL_H

#include "controls.h"
#include "steering_gear.h"
#include "marble.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl 과 Interface로 분리할지 고민중
*/

namespace controls
{
	using controls::SteeringGearControl;
	using components::marble_ptr;
	using components::SteeringGear;

	/*
		2016. 1. 13
		marble 을 그대로 가지고 있지 않고
		marble_ptr = unique_ptr 로 가지고 있을 것
	*/
	class SteeringGearControl
	{
	private:
		SteeringGear steeringGear;
		marble_ptr marbleCurrent;
		marble_ptr marbleNext;

		/*
			2016. 1. 13
			아직 미작성된 클래스
		*/
		//MarbleGenerator marbleGenerator;
		//Timer timer;

	public:
		SteeringGearControl();
		SteeringGearControl(const SteeringGearControl& rhs)=delete;
		virtual ~SteeringGearControl();
		SteeringGearControl& operator=(const SteeringGearControl& rhs)=delete;

		/*
			2016. 1. 13
			미작성
		*/

	};

}

#endif // _STEERING_GEAR_CONTROL_H