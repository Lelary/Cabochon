#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 1. 5.
	대체로 싱글톤
	2016. 1. 9.
	싱글톤으로 만드는 대신에 싱글톤 객체가 이 객체들을 가짐
	2016. 2. 2.
	Base 클래스로 Control 객체 작성. 기존 클래스들이 Control을 상속받음.
*/
namespace controls
{
	class Control;

	//LifeCycleControl has Timer
	class LifeCycleControl;

	//Timer는 여러군데 있을것 (1~2개)
	//각턴, 플레이타임
	class Timer;

	//MarbleControl has MarbleGenerator and a lot of Marble
	class MarbleControl;

	//SteeringGeerControl has a Marble or two Marbles
	/*
		2016. 1. 11
		여기서 Marble에 대한 factory를 수행함
	*/
	class SteeringWheelControl;

	//Generator가 따로 필요 할까?
	/*
		2016. 1. 13
		필요하지 않을까? 
		생성하는 경우		
			1. 맵 생성시
			2. SteeringWheelControl 에서

		Generator 라고 할지 Factory 라고 할지 결정해야함
	*/
	struct MarbleColorBitField;
	union MarbleColorOn;
	class MarbleBoard;
	class MarbleGenerator;



	// 나중에 구현
	// class LevelControl;
}
#endif