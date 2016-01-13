#ifndef _STEERING_GEAR_CONTROL_H
#define _STEERING_GEAR_CONTROL_H

#include "controls.h"
#include "steering_geer.h"
#include "marble.h"
#include "timer.h"
using controls::SteeringGearControl;
/*
	2016. 1. 13
	Impl �� Interface�� �и����� �����
*/
class SteeringGearControl
{
private:
	SteeringGear steeringGear;
	/*
		2016. 1. 13
		marble �� �״�� ������ ���� �ʰ�
		unique_ptr �� ������ ���� ��
	*/
	marble_ptr marbleCurrent;
	marble_ptr marbleNext;

	/*
		2016. 1. 13
		���� ���ۼ��� Ŭ����
	*/
	MarbleGenerator marbleGenerator;
	Timer timer;

public:
	SteeringGearControl();
	SteeringGearControl(const SteeringGearControl& rhs);
	virtual ~SteeringGearControl();
	SteeringGearControl& operator=(const SteeringGearControl& rhs);

	/*
		2016. 1. 13
		���ۼ�
	*/

};



#endif // _STEERING_GEAR_CONTROL_H