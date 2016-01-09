#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 1. 5.
	대체로 싱글톤
	2016. 1. 9.
	싱글톤으로 만드는 대신에 싱글톤 객체가 이 객체들을 가짐

*/
namespace controls
{
	//LifeCycleControl has Timer
	class LifeCycleControl;

	//Timer는 여러군데 있을것 (1~2개)
	//각턴, 플레이타임
	class Timer;

	//MarbleControl has MarbleGenerator and a lot of Marble
	class MarbleControl;

	//SteeringGeerControl has a Marble or two Marbles
	class SteeringGeerControl;

	//Generator가 따로 필요 할까?
	class MarbleGenerator;
	


	// 나중에 구현
	// class LevelControl;
}
#endif