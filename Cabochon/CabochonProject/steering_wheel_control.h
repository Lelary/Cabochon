#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
#include "control.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl �� Interface�� �и����� �����
*/

namespace controls
{
	using controls::SteeringWheelControl;
	using mathematics::scalar;
	using components::marble_ptr;
	using components::SteeringWheel;

	/*
		2016. 1. 13
		marble �� �״�� ������ ���� �ʰ�
		marble_ptr = unique_ptr �� ������ ���� ��
	*/
	class SteeringWheelControl
		:public Control
	{
	private:
		SteeringWheel _steeringWheel;
		marble_ptr _marbleCurrent;
		marble_ptr _marbleNext;

		/*
			2016. 1. 13
			���� ���ۼ��� Ŭ����
		*/
		//MarbleGenerator marbleGenerator;
		//Timer timer;

		/*
			2016. 1. 17
			��ư �Է� �ѹ��� ȸ���� ������ ����
			deltaTime ���� �ʿ����� üũ�ؾ���
			(Ű�Է� �߰� �Ŀ�)
		*/
		const int angularVelocity = 3;
		const int absMaxDegree = 81;

	public:
		SteeringWheelControl();
		SteeringWheelControl(const SteeringWheelControl& rhs)=delete;
		virtual ~SteeringWheelControl();
		SteeringWheelControl& operator=(const SteeringWheelControl& rhs)=delete;

		scalar getDegree() const;
		marble_ptr& getMarbleCurrent();
		marble_ptr& getMarbleNext();
		
		void setMarbleCurrent(marble_ptr& marble);
		void setMarbleNext(marble_ptr& marble);

		void setOrigin();
		void rotateLeft();
		void rotateRight();
		



	};

}

#endif // _STEERING_WHEEL_CONTROL_H