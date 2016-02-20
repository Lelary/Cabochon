#ifndef _STEERING_WHEEL_CONTROL_H
#define _STEERING_WHEEL_CONTROL_H

#include "controls.h"
#include "steering_wheel.h"
#include "marble.h"
#include "control.h"
#include "texture_list.h"
/*
	2016. 1. 13
	Impl �� Interface�� �и����� �����
*/

namespace controls
{
	using mathematics::scalar;
	using components::marble_ptr;
	using components::MarbleColor;
	using components::SteeringWheel;
	using controls::SteeringWheelControl;
	using scenes::TextureList;

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

		const scalar angularVelocity = 10;
		const scalar maxDegree = 70;

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