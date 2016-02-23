#include "cheat.h"
#include "steering_wheel_control.h"

using components::MarbleColor;
using controls::Cheat;
using controls::SteeringWheelControl;

void Cheat::cheatColor(SteeringWheelControl& wheelControl, MarbleColor color)
{
	if (color!=MarbleColor::None && color!=MarbleColor::Num)
		wheelControl.setMarbleCurrent(color);
}