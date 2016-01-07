#ifndef _CONTROLS_H
#define _CONTROLS_H

/*
	2016. 1. 5.
	��ü�� �̱���

*/
namespace controls
{
	//LifeCycleControl has Timer
	class LifeCycleControl;

	//Timer�� �������� ������ (1~2��)
	//����, �÷���Ÿ��
	class Timer;

	//MarbleControl has MarbleGenerator and a lot of Marble
	class MarbleControl;

	//SteeringGeerControl has a Marble or two Marbles
	class SteeringGeerControl;

	//Generator�� ���� �ʿ� �ұ�?
	class MarbleGenerator;
	
	// ���߿� ����
	// class LevelControl;
}
#endif