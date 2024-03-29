#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 2. 2.
	Base 클래스로 Control 객체 작성. 기존 클래스들이 Control을 상속받음.
*/
namespace controls
{
	class Control;
	class MarbleControl;
	class SteeringWheelControl;

	struct MarbleColorBitField;
	union MarbleColorOn;
	class MarbleBoard;
	class MarbleGenerator;

	class Cheat;
	
	// 2016. 3. 10. 추가.
	// drop 함수에서 사용할 클래스.
	class BoardLinkChecker;

	// 나중에 구현
	//class LifeCycleControl;
	//class Timer;
	// class LevelControl;
}
#endif