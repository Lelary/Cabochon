#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
#include "control.h"
//#include "timer.h"

/*
	2016. 1. 13
	Impl 과 Interface로 분리할지 고민중
*/

namespace controls
{
	using controls::SteeringWheelControl;
	using mathematics::scalar;
	using components::marble_ptr;
	using components::SteeringWheel;

	/*
		2016. 1. 13
		marble 을 그대로 가지고 있지 않고
		marble_ptr = unique_ptr 로 가지고 있을 것
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
			아직 미작성된 클래스
		*/
		//MarbleGenerator marbleGenerator;
		//Timer timer;

		/*
			2016. 1. 17
			버튼 입력 한번에 회전할 임의의 각도
			deltaTime 적용 필요한지 체크해야함
			(키입력 추가 후에)
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