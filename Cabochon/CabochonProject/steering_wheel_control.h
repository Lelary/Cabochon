#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
#include "control.h"
//#include "timer.h"
#include "texture_list.h"
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
	using scenes::TextureList; 
	using components::MarbleColor;

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

		const scalar _angularVelocity = 10;
		const scalar _maxDegree = 70;

	public:
		SteeringWheelControl();
		SteeringWheelControl(const SteeringWheelControl& rhs)=delete;
		virtual ~SteeringWheelControl();
		SteeringWheelControl& operator=(const SteeringWheelControl& rhs)=delete;

		void loadTextures(TextureList& texture);

		scalar getDegree() const;
		marble_ptr& getMarbleCurrent();
		marble_ptr& getMarbleNext();
		
		void setMarbleCurrent(MarbleColor color);
		void setMarbleNext(MarbleColor color);

		void setOrigin();
		void rotateLeft(float frameTime);
		void rotateRight(float frameTime);
		
		// pure virtual function
		virtual void render();
		virtual void update(float frameTime);
	};

}

#endif // _STEERING_WHEEL_CONTROL_H