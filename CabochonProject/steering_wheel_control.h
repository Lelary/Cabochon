#ifndef _STEERING_GEAR_CONTROL_H
#define _STEERING_GEAR_CONTROL_H

#include "controls.h"
#include "steering_gear.h"
#include "marble.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl �� Interface�� �и����� �����
*/

namespace controls
{
	using controls::SteeringGearControl;
	using components::marble_ptr;
	using components::SteeringGear;

	/*
		2016. 1. 13
		marble �� �״�� ������ ���� �ʰ�
		marble_ptr = unique_ptr �� ������ ���� ��
	*/
	class SteeringGearControl
	{
	private:
		SteeringGear steeringGear;
		marble_ptr marbleCurrent;
		marble_ptr marbleNext;

		/*
			2016. 1. 13
			���� ���ۼ��� Ŭ����
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
			���ۼ�
		*/

	};

}

#endif // _STEERING_GEAR_CONTROL_H