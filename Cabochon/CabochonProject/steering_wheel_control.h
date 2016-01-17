#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl �� Interface�� �и����� �����
*/

namespace controls
{
	using controls::SteeringWheelControl;
	using components::marble_ptr;
	using components::SteeringWheel;

	/*
		2016. 1. 13
		marble �� �״�� ������ ���� �ʰ�
		marble_ptr = unique_ptr �� ������ ���� ��
	*/
	class SteeringWheelControl
	{
	private:
		SteeringWheel steeringWheel;
		marble_ptr marbleCurrent;
		marble_ptr marbleNext;

		/*
			2016. 1. 13
			���� ���ۼ��� Ŭ����
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
			���ۼ�
		*/

	};

}

#endif // _STEERING_WHEEL_CONTROL_H